/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Debug.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/AuthListener.h>
#include <alljoyn/AboutProxy.h>
#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
#include <alljoyn/hae/DeviceListener.h>
#include "AutoLock.h"
#include "HaeConstants.h"
#include "HaeControllerImpl.h"
#include "HaeBusListener.h"
#include "HaeAboutCustomFields.h"
#include "InterfaceFactory.h"
#include <alljoyn/hae/HaeProxyBusObject.h>

using namespace ajn;
using namespace services;
using namespace qcc;

HaeControllerImpl::HaeControllerImpl(BusAttachment& bus, DeviceListener* listener)
: m_isStarted(false)
, m_bus(bus)
, m_haeBusListener(m_bus)
, m_deviceListener(listener)
{
    m_haeBusListener.SetSessionPort(HAE_SERVICE_PORT);

    QStatus status = InterfaceFactory::GetInstance()->InitInterfaceFactory(&m_bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: Interface factory initialization  is failed.", __func__));
    }

    m_security.m_authMechanisms = NULL;
    m_security.m_authListener = NULL;
    m_security.m_keyStoreFileName = NULL;
    m_security.m_isKeyStoreShared = NULL;

}

HaeControllerImpl::~HaeControllerImpl()
{
}

QStatus HaeControllerImpl::EnablePeerSecurity(const char* authMechanisms,
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

QStatus HaeControllerImpl::Init(const InterestDeviceList& list)
{
    return ER_OK;
}

QStatus HaeControllerImpl::Start()
{
    QStatus status = ER_OK;

    AutoLock lock(m_lock);
    if (m_isStarted) {
        QCC_DbgPrintf(("%s: HaeController is already started.", __func__));
        return ER_OK;
    }

    if (m_security.m_authListener && m_security.m_authMechanisms) {
        status = m_bus.EnablePeerSecurity(m_security.m_authMechanisms, m_security.m_authListener, m_security.m_keyStoreFileName, m_security.m_isKeyStoreShared);
        if (status != ER_OK) {
            return status;
        }
    }

    m_bus.RegisterBusListener(m_haeBusListener);
    m_bus.RegisterAboutListener(*this);

    const char* interfaces[] = { "*" };
    status = m_bus.WhoImplements(interfaces, sizeof(interfaces) / sizeof(interfaces[0]));
    if (status != ER_OK) {
        return status;
    }

    m_isStarted = true;

    QCC_DbgPrintf(("%s: HaeController started.", __func__));

    return status;
}

QStatus HaeControllerImpl::Stop()
{
    QStatus status = ER_OK;
    AutoLock lock(m_lock);
    if (!m_isStarted) {
        QCC_DbgPrintf(("%s: HaeController is already stopped.", __func__));
        return ER_OK;
    }

    m_bus.UnregisterAboutListener(*this);
    m_bus.UnregisterBusListener(m_haeBusListener);

    m_isStarted = false;

    return status;
}

QStatus HaeControllerImpl::JoinDevice(const std::string& busName, SessionPort port, const HaeAboutData& data,
                                      AboutObjectDescription& description)
{
    SessionId sessionId;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    QStatus status = m_bus.JoinSession(busName.c_str(), port, this, sessionId, opts);
    QCC_DbgPrintf(("SessionJoined sessionId = %u, status = %s\n", sessionId, QCC_StatusText(status)));

    if (ER_OK == status && 0 != sessionId) {
        DeviceInfoPtr info(new DeviceInfo(busName.c_str(), sessionId, port, data, description));
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

HaeInterface* HaeControllerImpl::CreateInterface(const HaeInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener)
{
    QStatus status = ER_OK;
    HaeInterface* interface = NULL;
    {
        AutoLock lock(m_lock);
        if (!m_isStarted) {
            status = ER_FAIL;
            QCC_LogError(status, ("%s: HaeControllee is currently stopped.", __func__));
            return NULL;
        }
    }

    if (InterfaceTypesMap.find(type) == InterfaceTypesMap.end()) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: Function call argument 1 is invalid.", __func__));
        return NULL;
    }

    if (objectPath.empty()) {
        QCC_LogError(ER_BAD_ARG_2, ("%s: Function call argument 2 is invalid.", __func__));
        return NULL;
    }

    HaeProxyBusObject* haeProxyObject = NULL;
    DeviceInfoPtr info(new DeviceInfo());
    status = m_deviceManager.FindDeviceInfoByBusName(busName, info);
    if (ER_OK != status) {
        QCC_LogError(status, ("Device is not exist.", __func__));
        return NULL;
    } else {
        haeProxyObject = info->GetHaeProxyBusObject(m_bus, objectPath);
        if(!haeProxyObject) {
            status = ER_FAIL;
            QCC_LogError(status, ("Failed to get proxy bus object.", __func__));
            return NULL;
        }
    }

    interface = haeProxyObject->CreateInterface(type, listener);
    if (!interface) {
        QCC_LogError(ER_FAIL, ("%s: could not create interface.", __func__));
        delete haeProxyObject;
        return NULL;
    }

    return interface;
}

const HaeInterfaceType HaeControllerImpl::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController)
{
    InterfaceFactory* factory = InterfaceFactory::GetInstance();
    HaeInterfaceType type = UNDEFINED_INTERFACE;
    uint32_t vendorCnt = 0;

    std::map<HaeInterfaceType, qcc::String>::iterator it;
    for (it = InterfaceTypesMap.begin(); it != InterfaceTypesMap.end(); ++it) {
        type = it->first;
        if (type >= VENDOR_DEFINED_INTERFACE) {
            ++vendorCnt;
        }

        if (!interfaceName.compare(it->second)) {
            CreateIntfControllerFptr registeredFptr = factory->GetCreateIntfControllerFptr(type);

            if (registeredFptr == createIntfController) {
                QCC_DbgPrintf(("%s: Vendor defined interface is already registered.", __func__));
            } else {
                factory->RegisterVendorDefinedIntfController(type, createIntfController);
            }
            return type;
        }
    }

    // Add new interface type
    HaeInterfaceType newVendorType = VENDOR_DEFINED_INTERFACE + vendorCnt;

    InterfaceTypesMap[newVendorType] = interfaceName;
    factory->RegisterVendorDefinedIntfController(newVendorType, createIntfController);

    return newVendorType;
}

/*
QStatus HaeControllerImpl::GetAboutObjectDescription(const DeviceInfo& deviceInfo, AboutObjectDescription& aboutObjectDesc)
{
    QStatus status = ER_OK;
    SessionId sessionId = deviceInfo.GetSessionId();

    if (sessionId == 0) {
        status = ER_FAIL;
        QCC_LogError(status, ("Session is not exist"));
        return status;
    }

    AboutProxy aboutProxy(m_bus, deviceInfo.GetBusName().c_str(), sessionId);
    MsgArg objectDesc;

    status = aboutProxy.GetObjectDescription(objectDesc);
    if (status != ER_OK) {
        QCC_LogError(status, ("GetObjectDescription is failed."));
        return status;
    }

    status = aboutObjectDesc.CreateFromMsgArg(objectDesc);
    if (status != ER_OK) {
        QCC_LogError(status, ("CreateFromMsgArg is failed."));
        return status;
    }

    return status;
}
*/
void HaeControllerImpl::Announced(const char* busName, uint16_t version, SessionPort port, const MsgArg& objectDescriptionArg, const MsgArg& aboutDataArg)
{
    QCC_DbgPrintf(("%s", __func__));

    if ( !m_isStarted ) {
        QCC_DbgPrintf(("%s: Controller Client is stopped. Returning without processing announcement.", __func__));
        return;
    }

    QStatus status = ER_OK;
    MsgArg* deviceTypeArg = NULL;
    MsgArg* elemArg = NULL;
    size_t elemCount = 0;
    AboutObjectDescription objectDescs(objectDescriptionArg);

    char* deviceID = NULL;
    char* deviceName = NULL;

    m_bus.EnableConcurrentCallbacks();

    HaeAboutData aboutData(aboutDataArg);

    aboutData.GetDeviceId(&deviceID);
    aboutData.GetDeviceName(&deviceName);

    QCC_DbgPrintf(("%s: Received Announce: busName=%s port=%u deviceID=%s deviceName=%s rank=%s isLeader=%d", __func__, busName, port, deviceID, deviceName));

    status = aboutData.GetField(DEVICE_TYPE_DESCRIPTION.c_str(), deviceTypeArg);
    if (status != ER_OK) {
        QCC_DbgPrintf(("Error (%d)", status));
        return;

    } else if (!deviceTypeArg) {
        return;
    }

    status = deviceTypeArg->Get(aboutData.GetFieldSignature(DEVICE_TYPE_DESCRIPTION.c_str()), &elemCount, &elemArg);
    if (status != ER_OK) {
        QCC_DbgPrintf(("Error (%d)", status));
        return;
    }

    if (elemCount > 0) {
        m_deviceListener->OnDeviceAdded(busName, port, aboutData, objectDescs);
    }
}

void HaeControllerImpl::SessionLost(ajn::SessionId sessionId, ajn::SessionListener::SessionLostReason reason)
{
    QCC_UNUSED(sessionId);
    QCC_UNUSED(reason);
    QCC_DbgPrintf(("Session lost for sessionId: %u", sessionId));

    if (m_deviceListener) {
        m_deviceListener->OnDeviceSessionLost(sessionId);
    }
}

/*
void HaeControllerImpl::JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context)
{
    if (status != ER_OK) {
        QCC_LogError(status, ("Joining session failed."));
////        ControlPanelListener* listener = m_Device->getListener();
////        if (listener) {
////            listener->errorOccured(m_Device, status, SESSION_JOIN, "Could not join session");
////        }
        return;
    }
//
    QCC_DbgPrintf(("Joining session succeeded. SessionId: %u", id));
//
    if (m_deviceListener) {
        DeviceInfoPtr info;
        if (ER_OK == m_deviceManager.FindDeviceInfo(id, info)) {
            m_deviceListener->OnDeviceSessionJoined(info);
        }
    }
}
*/
