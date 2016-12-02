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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControllerListener.h>

#include "CurrentAirQualityLevelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CurrentAirQualityLevelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new CurrentAirQualityLevelIntfControllerImpl(busAttachment, dynamic_cast<CurrentAirQualityLevelIntfControllerListener&>(listener), cdmProxyObject);
}

CurrentAirQualityLevelIntfControllerImpl::CurrentAirQualityLevelIntfControllerImpl(BusAttachment& busAttachment, CurrentAirQualityLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

CurrentAirQualityLevelIntfControllerImpl::~CurrentAirQualityLevelIntfControllerImpl()
{
}

QStatus CurrentAirQualityLevelIntfControllerImpl::Init()
{
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    return status;
}

void CurrentAirQualityLevelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_ContaminantType.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnContaminantTypeChanged(obj.GetPath(), (ContaminantType)value);
            }
        }
        else if (!s_prop_CurrentLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnCurrentLevelChanged(obj.GetPath(), value);
            }
        }
        else if (!s_prop_MaxLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnMaxLevelChanged(obj.GetPath(), value);
            }
        }
    }
}

void CurrentAirQualityLevelIntfControllerImpl::GetContaminantTypePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetContaminantType(status, obj->GetPath(), (ContaminantType)val, context);
}

void CurrentAirQualityLevelIntfControllerImpl::GetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetCurrentLevel(status, obj->GetPath(), val, context);
}

void CurrentAirQualityLevelIntfControllerImpl::GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMaxLevel(status, obj->GetPath(), val, context);
}

QStatus CurrentAirQualityLevelIntfControllerImpl::GetContaminantType(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_ContaminantType.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityLevelIntfControllerImpl::GetContaminantTypePropertyCB, context);
    return status;
}

QStatus CurrentAirQualityLevelIntfControllerImpl::GetCurrentLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_CurrentLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityLevelIntfControllerImpl::GetCurrentLevelPropertyCB, context);
    return status;
}

QStatus CurrentAirQualityLevelIntfControllerImpl::GetMaxLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityLevelIntfControllerImpl::GetMaxLevelPropertyCB, context);
    return status;
}

} //namespace services
} //namespace ajn
