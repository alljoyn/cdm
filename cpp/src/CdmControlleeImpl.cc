/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Debug.h>
#include <qcc/String.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/AuthListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

#include "AutoLock.h"
#include "CdmBusListener.h"
#include "CdmConstants.h"
#include "InterfaceFactory.h"
#include "CdmControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmControlleeImpl::CdmControlleeImpl(BusAttachment& bus, CdmAboutData* aboutData) :
    m_bus(bus),
    m_aboutData(aboutData),
    m_cdmBusListener(new CdmBusListener(m_bus)),
    m_isStarted(false)
{
    m_cdmBusListener->SetSessionPort(CDM_SERVICE_PORT);

    m_security.m_authMechanisms = NULL;
    m_security.m_authListener = NULL;
    m_security.m_keyStoreFileName = NULL;
    m_security.m_isKeyStoreShared = false;

    QStatus status = InterfaceFactory::GetInstance()->InitInterfaceFactory(&m_bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: Interface factory initialization is failed.", __func__));
    }
}

CdmControlleeImpl::~CdmControlleeImpl()
{
    map<String, CdmBusObject*>::const_iterator it;
    for (it = m_cdmBusObjectsMap.begin(); it != m_cdmBusObjectsMap.end(); ++it) {
        CdmBusObject* cdmBusObject = it->second;

        if (cdmBusObject) {
            delete cdmBusObject;
            cdmBusObject = 0;
        }
    }

    if (m_cdmBusListener) {
        delete m_cdmBusListener;
    }
}

QStatus CdmControlleeImpl::EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared)
{
    AutoLock lock(m_lock);
    if (m_isStarted) {
        QCC_DbgPrintf(("%s: CdmControllee is already started.", __func__));
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

QStatus CdmControlleeImpl::Start()
{
    QStatus status = ER_OK;

    AutoLock lock(m_lock);
    if (m_isStarted) {
        QCC_DbgPrintf(("%s: CdmControllee is already started.", __func__));
        return ER_OK;
    }

    if (!m_aboutData) {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: AboutData is not exist.", __func__));
        return status;
    }

    status = RegisterBusObject();
    if (status != ER_OK) {
        return status;
    }

    if (m_security.m_authListener && m_security.m_authMechanisms) {
        status = m_bus.EnablePeerSecurity(m_security.m_authMechanisms, m_security.m_authListener, m_security.m_keyStoreFileName, m_security.m_isKeyStoreShared);
        if (status != ER_OK) {
            return status;
        }
    }

    status = RegisterBusListener(m_cdmBusListener);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: CdmBus listener registration is failed.", __func__));
        goto cleanup;
    }

    status = CheckAboutDeviceTypeValidation();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: About device type is invalid.", __func__));
        return status;
    }

    m_isStarted = true;
    return status;

cleanup:
    QStatus ret = ER_OK;
    ret = UnregisterBusListener(m_cdmBusListener);
    if (ret != ER_OK) {
        QCC_LogError(ret, ("%s: CdmBus listener unregistration is failed.", __func__));
    }
    return status;
}

QStatus CdmControlleeImpl::Stop()
{
    QStatus status = ER_OK;
    AutoLock lock(m_lock);
    if (!m_isStarted) {
        QCC_DbgPrintf(("%s: CdmControllee is already stopped.", __func__));
        return ER_OK;
    }

    QStatus ret = ER_OK;
    ret = UnregisterBusListener(m_cdmBusListener);
    if (ret != ER_OK) {
        QCC_LogError(ret, ("%s: CdmBus listener unregistration is failed.", __func__));
    }

    m_isStarted = false;

    return status;
}

CdmInterface* CdmControlleeImpl::CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener)
{
    QStatus status = ER_OK;
    CdmInterface* interface = NULL;
    {
        AutoLock lock(m_lock);
        if (m_isStarted) {
            status = ER_FAIL;
            QCC_LogError(status, ("%s: CdmControllee is already started.", __func__));
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

    CdmBusObject* cdmBusObject = NULL;
    map<String, CdmBusObject*>::const_iterator it = m_cdmBusObjectsMap.find(objectPath);
    if (it != m_cdmBusObjectsMap.end()) {
        cdmBusObject = it->second;
    } else {
        cdmBusObject = new CdmBusObject(m_bus, objectPath);
        if (!cdmBusObject) {
            QCC_LogError(ER_OUT_OF_MEMORY, ("%s: could not create CdmBusObject class.", __func__));
            return NULL;
        }
        m_cdmBusObjectsMap[objectPath] = cdmBusObject;
    }

    interface = cdmBusObject->CreateInterface(type, listener);
    if (!interface) {
        QCC_LogError(ER_FAIL, ("%s: could not register bus object to bus attachment.", __func__));
        delete cdmBusObject;
        return NULL;
    }

    return interface;
}

const CdmInterfaceType CdmControlleeImpl::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee)
{
    InterfaceFactory* factory = InterfaceFactory::GetInstance();
    CdmInterfaceType type = UNDEFINED_INTERFACE;
    uint32_t vendorCnt = 0;

    std::map<CdmInterfaceType, qcc::String>::iterator it;
    for (it = InterfaceTypesMap.begin(); it != InterfaceTypesMap.end(); ++it) {
        type = it->first;
        if (type >= VENDOR_DEFINED_INTERFACE) {
            ++vendorCnt;
        }

        if (!interfaceName.compare(it->second)) {
            CreateIntfControlleeFptr registeredFptr = factory->GetCreateIntfControlleeFptr(type);

            if (registeredFptr == createIntfControllee) {
                QCC_DbgPrintf(("%s: Vendor defined interface is already registered.", __func__));
            } else {
                factory->RegisterVendorDefinedIntfControllee(type, createIntfControllee);
            }
            return type;
        }
    }

    // Add new interface type
    CdmInterfaceType newVendorType = VENDOR_DEFINED_INTERFACE + vendorCnt;

    InterfaceTypesMap[newVendorType] = interfaceName;
    factory->RegisterVendorDefinedIntfControllee(newVendorType, createIntfControllee);

    return newVendorType;
}

QStatus CdmControlleeImpl::CheckAboutDeviceTypeValidation()
{
    QStatus status;
    MsgArg* deviceTypeArg = NULL;
    MsgArg* elemArg = NULL;
    size_t elemCount = 0;
    DeviceType deviceType;
    const char* objectPath = NULL;

    if (!m_aboutData) {
        return ER_INVALID_DATA;
    }

    status = m_aboutData->GetField(CdmAboutData::DEVICE_TYPE_DESCRIPTION.c_str(), deviceTypeArg);
    if (status != ER_OK) {
        return status;
    } else if (!deviceTypeArg) {
        return ER_FAIL;
    }

    status = deviceTypeArg->Get(m_aboutData->GetFieldSignature(CdmAboutData::DEVICE_TYPE_DESCRIPTION.c_str()), &elemCount, &elemArg);
    if (status != ER_OK) {
        return status;
    }

    for (size_t i=0; i<elemCount; ++i) {
        status = elemArg[i].Get("(uo)", &deviceType, &objectPath);
        if (status != ER_OK) {
            return status;
        }

        if (!objectPath || deviceType < 0 || deviceType > MAX_DEVICE_TYPE) {
            return ER_FAIL;
        }

        if (m_cdmBusObjectsMap.find(objectPath) == m_cdmBusObjectsMap.end()) {
            return ER_FAIL;
        }
    }
    return status;
}

QStatus CdmControlleeImpl::RegisterBusObject()
{
    QStatus status = ER_OK;

    /* Register bus objects */
    for (map<String, CdmBusObject*>::const_iterator it = m_cdmBusObjectsMap.begin(); it != m_cdmBusObjectsMap.end(); ++it ) {
        CdmBusObject* cdmBusObject = it->second;
        status = m_bus.RegisterBusObject(*cdmBusObject, false);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: could not register bus object(%s) to bus attachment.", __func__, it->first.c_str()));
            return status;
        }
    }
    return status;
}


QStatus CdmControlleeImpl::RegisterBusListener(CdmBusListener* listener, TransportMask transportMask)
{
    QStatus status = ER_OK;

    if (!listener) {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: CdmBusListener is not allocated.", __func__));
        return status;
    }

    m_bus.RegisterBusListener(*listener);

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, transportMask);
    SessionPort port = listener->GetSessionPort();
    status = m_bus.BindSessionPort(port, opts, *listener);

    return status;
}

QStatus CdmControlleeImpl::UnregisterBusListener(CdmBusListener* listener)
{
    QStatus status = ER_OK;

    if (!listener) {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: CdmBusListener is not allocated.", __func__));
        return status;
    }

    m_bus.UnregisterBusListener(*listener);
    status = m_bus.UnbindSessionPort(listener->GetSessionPort());

    return status;
}

} //namespace services
} //namespace ajn