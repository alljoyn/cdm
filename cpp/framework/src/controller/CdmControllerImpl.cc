/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Debug.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/AuthListener.h>
#include <alljoyn/AboutProxy.h>
#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <alljoyn/cdm/common/DeviceListener.h>
#include "../common/AutoLock.h"
#include "../common/CdmConstants.h"
#include "CdmControllerImpl.h"
#include "../common/CdmBusListener.h"
#include "interfaces/controller/ControllerFactory.h"

using namespace ajn;
using namespace services;
using namespace qcc;

CdmControllerImpl::CdmControllerImpl(BusAttachment& bus, DeviceListener* listener)
: m_isStarted(false)
, m_bus(bus)
, m_cdmBusListener(m_bus)
, m_deviceListener(listener)
{
    m_cdmBusListener.SetSessionPort(CDM_SERVICE_PORT);

    QStatus status = ControllerFactory::Instance().InitControllerFactory(&m_bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: Interface factory initialization is failed.", __func__));
    }

    m_security.m_authMechanisms = NULL;
    m_security.m_authListener = NULL;
    m_security.m_keyStoreFileName = NULL;
    m_security.m_isKeyStoreShared = false;

}

CdmControllerImpl::~CdmControllerImpl()
{
}

QStatus CdmControllerImpl::EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared)
{
    AutoLock lock(m_lock);
    if (m_isStarted) {
        QCC_DbgPrintf(("%s: Service is already started.", __func__));
        return ER_BUS_ALREADY_CONNECTED;
    }

    if (!authMechanisms) {
        return ER_BAD_ARG_1;
    }
    if (!authListener) {
        return ER_BAD_ARG_2;
    }

    m_security.m_authMechanisms = authMechanisms;
    m_security.m_authListener = authListener;
    m_security.m_keyStoreFileName = keyStoreFileName;
    m_security.m_isKeyStoreShared = isKeyStoreShared;

    return ER_OK;
}

QStatus CdmControllerImpl::Init(const InterestDeviceList& list)
{
    return ER_OK;
}

QStatus CdmControllerImpl::Start()
{
    QStatus status = ER_OK;

    AutoLock lock(m_lock);
    if (m_isStarted) {
        QCC_DbgPrintf(("%s: CdmController is already started.", __func__));
        return ER_OK;
    }

    if (m_security.m_authListener && m_security.m_authMechanisms) {
        status = m_bus.EnablePeerSecurity(m_security.m_authMechanisms, m_security.m_authListener, m_security.m_keyStoreFileName, m_security.m_isKeyStoreShared);
        if (status != ER_OK) {
            return status;
        }
    }

    m_bus.RegisterBusListener(m_cdmBusListener);
    m_bus.RegisterAboutListener(*this);

    const char* interfaces[] = { "*" };
    status = m_bus.WhoImplements(interfaces, sizeof(interfaces) / sizeof(interfaces[0]));
    if (status != ER_OK) {
        return status;
    }

    m_isStarted = true;

    QCC_DbgPrintf(("%s: CdmController started.", __func__));

    return status;
}

QStatus CdmControllerImpl::Stop()
{
    QStatus status = ER_OK;
    AutoLock lock(m_lock);
    if (!m_isStarted) {
        QCC_DbgPrintf(("%s: CdmController is already stopped.", __func__));
        return ER_OK;
    }

    m_bus.UnregisterAboutListener(*this);
    m_bus.UnregisterBusListener(m_cdmBusListener);

    m_isStarted = false;

    return status;
}

QStatus CdmControllerImpl::JoinDevice(const std::string& busName, SessionPort port, const CdmAboutData& data,
                                      AboutObjectDescription& description)
{
    SessionId sessionId;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    QStatus status = m_bus.JoinSession(busName.c_str(), port, this, sessionId, opts);
    QCC_DbgPrintf(("SessionJoined sessionId = %u, status = %s\n", sessionId, QCC_StatusText(status)));

    if (ER_OK == status && 0 != sessionId) {
        Ref<DeviceInfo> info(new DeviceInfo(busName.c_str(), sessionId, port, data, description));
        QStatus ret = m_deviceManager.AddDeviceInfo(info);
        if (ER_OK == ret && m_deviceListener) {
            m_deviceListener->OnDeviceSessionJoined(info);
        }

        AboutProxy aboutProxy(m_bus, busName.c_str(), sessionId);
        MsgArg objectDesc;

        ret = aboutProxy.GetObjectDescription(objectDesc);
        if (ER_OK == ret) {
            ret = description.CreateFromMsgArg(objectDesc);
            if (ER_OK != ret) {
                QCC_LogError(status, ("CreateFromMsgArg is failed."));
            }
        }
    }
    return status;
}

Ref<CdmInterface> CdmControllerImpl::CreateInterface(const std::string& interfaceName, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, Ref<InterfaceControllerListener> listener)
{
    QStatus status = ER_OK;
    Ref<CdmInterface> interface = NULL;

    {
        AutoLock lock(m_lock);
        if (!m_isStarted) {
            status = ER_FAIL;
            QCC_LogError(status, ("%s: CdmControllee is currently stopped.", __func__));
            return interface;
        }
    }

    if (!ControllerFactory::Instance().GetCreateIntfControllerFptr(interfaceName)) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: Function call argument 1 is invalid.", __func__));
        return interface;
    }

    if (objectPath.empty()) {
        QCC_LogError(ER_BAD_ARG_2, ("%s: Function call argument 2 is invalid.", __func__));
        return interface;
    }

    auto pbo = mkRef<ProxyBusObject>(m_bus, busName.c_str(), objectPath.c_str(), sessionId);

    interface = ControllerFactory::Instance().CreateIntfController(interfaceName, listener, pbo);

    if (!interface) {
        QCC_LogError(ER_FAIL, ("%s: could not create interface.", __func__));
        return NULL;
    }

    const InterfaceDescription* description = interface->GetInterfaceDescription();
    status = pbo->AddInterface(*description);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not add interface.", __func__));
        return NULL;
    }

    return interface;
}



QStatus CdmControllerImpl::RegisterInterface(const std::string& interfaceName, CreateIntfControllerFptr createIntfController)
{
    return ControllerFactory::Instance().RegisterIntfController(interfaceName, createIntfController);
}



QStatus CdmControllerImpl::UnregisterInterface(const std::string& interfaceName, CreateIntfControllerFptr createIntfController)
{
    return ControllerFactory::Instance().UnregisterIntfController(interfaceName, createIntfController);
}



void CdmControllerImpl::Announced(const char* busName, uint16_t version, SessionPort port, const MsgArg& objectDescriptionArg, const MsgArg& aboutDataArg)
{
    QCC_DbgPrintf(("%s", __func__));

    if ( !m_isStarted ) {
        QCC_DbgPrintf(("%s: Controller Client is stopped. Returning without processing announcement.", __func__));
        return;
    }

    AboutObjectDescription objectDescs(objectDescriptionArg);

    char* deviceID = NULL;
    char* deviceName = NULL;

    m_bus.EnableConcurrentCallbacks();

    CdmAboutData aboutData(aboutDataArg);

    aboutData.GetDeviceId(&deviceID);
    aboutData.GetDeviceName(&deviceName);

    QCC_DbgPrintf(("%s: Received Announce: busName=%s port=%u deviceID=%s deviceName=%s", __func__, busName, port, deviceID, deviceName));

    m_deviceListener->OnDeviceAdded(busName, port, aboutData, objectDescs);
}

void CdmControllerImpl::SessionLost(ajn::SessionId sessionId, ajn::SessionListener::SessionLostReason reason)
{
    QCC_UNUSED(sessionId);
    QCC_UNUSED(reason);
    QCC_DbgPrintf(("Session lost for sessionId: %u", sessionId));

    if (m_deviceListener) {
        m_deviceListener->OnDeviceSessionLost(sessionId);
    }
}