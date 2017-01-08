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
#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include "../common/CdmBusListener.h"
#include "../common/CdmConstants.h"
#include "CdmControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmControlleeImpl::CdmControlleeImpl(BusAttachment& bus) :
    m_bus(bus),
    m_cdmBusListener(new CdmBusListener(m_bus)),
    m_isStarted(false),
    m_emitChangedOnSet(false)
{
    m_cdmBusListener->SetSessionPort(CDM_SERVICE_PORT);
}


CdmControlleeImpl::~CdmControlleeImpl()
{
    delete m_cdmBusListener;
}


QStatus CdmControlleeImpl::Start(bool emitOnSetProperty)
{
    QStatus status = ER_OK;

    if (m_isStarted) {
        QCC_DbgPrintf(("%s: CdmControllee is already started.", __func__));
        return ER_OK;
    }

    status = RegisterBusObjects();
    if (status != ER_OK) {
        return status;
    }

    status = RegisterBusListener();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: CdmBus listener registration is failed.", __func__));
        return status;
    }

    m_emitChangedOnSet = emitOnSetProperty;
    m_isStarted = true;
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

bool CdmControlleeImpl::EmitChangedSignalOnSet() const
{
    return m_emitChangedOnSet;
}

Ref<CdmBusObject> CdmControlleeImpl::GetCdmBusObject(const qcc::String &busPath)
{
    Ref<CdmBusObject> cdmBusObject;

    auto iter = m_cdmBusObjectsMap.find(busPath);
    bool created = false;

    if (iter != m_cdmBusObjectsMap.end()) {
        cdmBusObject = iter->second;
    } else {
        cdmBusObject = Ref<CdmBusObject>(new CdmBusObject(m_bus, busPath));
        created = true;
    }

    if (created)
    {
        m_cdmBusObjectsMap[busPath] = cdmBusObject;
    }

    return cdmBusObject;
}

QStatus CdmControlleeImpl::RegisterBusObjects()
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

Ref<CdmControlleeInterface> CdmControlleeImpl::GetCdmInterface(const qcc::String& busPath, const qcc::String& interfaceName)
{
    std::pair<qcc::String, qcc::String> key = {busPath, interfaceName};
    return (m_interfaces.find(key) != m_interfaces.end()) ? m_interfaces[key] : Ref<CdmControlleeInterface>();
}

void CdmControlleeImpl::RegisterCdmInterface(const qcc::String& busPath, const qcc::String& interfaceName, Ref<CdmControlleeInterface> interface)
{
    m_interfaces[{busPath, interfaceName}] = interface;
}

} //namespace services
} //namespace ajn
