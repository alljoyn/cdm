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
#include <qcc/String.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/AuthListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/CdmAnnouncer.h>
#include <alljoyn/cdm/CdmSecurity.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

#include "CdmBusListener.h"
#include "CdmConstants.h"
#include "InterfaceFactory.h"
#include "CdmControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmControlleeImpl::CdmControlleeImpl(
    BusAttachment& bus,
    Ref<CdmAnnouncer> announcer,
    Ref<CdmSecurity> security
    ) :
    m_bus(bus),
    m_announcer(announcer),
    m_security(security),
    m_cdmBusListener(new CdmBusListener(m_bus)),
    m_isStarted(false)
{
    m_cdmBusListener->SetSessionPort(CDM_SERVICE_PORT);

    QStatus status = InterfaceFactory::GetInstance()->InitInterfaceFactory(&m_bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: Interface factory initialization is failed.", __func__));
    }
}


CdmControlleeImpl::~CdmControlleeImpl()
{
    delete m_cdmBusListener;
}


QStatus CdmControlleeImpl::Start()
{
    QStatus status = ER_OK;

    if (m_isStarted) {
        QCC_DbgPrintf(("%s: CdmControllee is already started.", __func__));
        return ER_OK;
    }

    status = RegisterBusObject();
    if (status != ER_OK) {
        return status;
    }

    if (m_security) {
        status = m_security->Enable();
        if (status != ER_OK) {
            return status;
        }
    }

    status = RegisterBusListener();
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
    ret = UnregisterBusListener();
    if (ret != ER_OK) {
        QCC_LogError(ret, ("%s: CdmBus listener unregistration is failed.", __func__));
    }
    return status;
}

QStatus CdmControlleeImpl::Stop()
{
    QStatus status = ER_OK;

    if (!m_isStarted) {
        QCC_DbgPrintf(("%s: CdmControllee is already stopped.", __func__));
        return ER_OK;
    }

    QStatus ret = ER_OK;
    ret = UnregisterBusListener();
    if (ret != ER_OK) {
        QCC_LogError(ret, ("%s: CdmBus listener unregistration is failed.", __func__));
    }

    m_isStarted = false;

    return status;
}

CdmInterface* CdmControlleeImpl::CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener)
{
    QStatus status = ER_OK;
    {
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

    Ref<CdmBusObject> cdmBusObject;

    auto iter = m_cdmBusObjectsMap.find(objectPath);
    bool created = false;

    if (iter != m_cdmBusObjectsMap.end()) {
        cdmBusObject = iter->second;
    } else {
        cdmBusObject = Ref<CdmBusObject>(new CdmBusObject(m_bus, objectPath));
        created = true;
    }

    auto interface = cdmBusObject->CreateInterface(type, listener);

    if (!interface) {
        QCC_LogError(ER_FAIL, ("%s: could not register bus object to bus attachment.", __func__));
        return NULL;
    }

    if (created)
    {
        m_cdmBusObjectsMap[objectPath] = cdmBusObject;
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
    DeviceTypeDescription devTypes = m_announcer->GetAboutData()->GetDeviceTypeDescription();

    for (auto& pair : devTypes.GetDescriptions()) {
        auto& deviceType = pair.first;
        auto& objectPath = pair.second;

        if (m_cdmBusObjectsMap.find(objectPath) == m_cdmBusObjectsMap.end()) {
            return ER_FAIL;
        }
    }

    return ER_OK;
}

QStatus CdmControlleeImpl::RegisterBusObject()
{
    /* Register bus objects */
    for (auto& pair : m_cdmBusObjectsMap) {
        auto status = m_bus.RegisterBusObject(*pair.second, false);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: could not register bus object(%s) to bus attachment.", __func__, pair.first.c_str()));
            return status;
        }
    }

    return ER_OK;
}


QStatus CdmControlleeImpl::RegisterBusListener()
{
    m_bus.RegisterBusListener(*m_cdmBusListener);

    TransportMask transportMask = TRANSPORT_ANY;

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, transportMask);
    SessionPort port = m_cdmBusListener->GetSessionPort();
    auto status = m_bus.BindSessionPort(port, opts, *m_cdmBusListener);

    return status;
}

QStatus CdmControlleeImpl::UnregisterBusListener()
{
    m_bus.UnregisterBusListener(*m_cdmBusListener);
    auto status = m_bus.UnbindSessionPort(m_cdmBusListener->GetSessionPort());

    return status;
}

} //namespace services
} //namespace ajn
