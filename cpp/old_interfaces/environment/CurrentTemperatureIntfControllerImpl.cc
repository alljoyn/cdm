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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllerListener.h>
#include "CurrentTemperatureIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CurrentTemperatureIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new CurrentTemperatureIntfControllerImpl(busAttachment, dynamic_cast<CurrentTemperatureIntfControllerListener&>(listener), cdmProxyObject);
}

CurrentTemperatureIntfControllerImpl::CurrentTemperatureIntfControllerImpl(BusAttachment& busAttachment, CurrentTemperatureIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

CurrentTemperatureIntfControllerImpl::~CurrentTemperatureIntfControllerImpl()
{
}

QStatus CurrentTemperatureIntfControllerImpl::Init()
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

QStatus CurrentTemperatureIntfControllerImpl::GetCurrentValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_CurrentValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentTemperatureIntfControllerImpl::GetCurrentValuePropertyCB, context);
    return status;
}

QStatus CurrentTemperatureIntfControllerImpl::GetPrecision(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Precision.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentTemperatureIntfControllerImpl::GetPrecisionPropertyCB, context);
    return status;
}

QStatus CurrentTemperatureIntfControllerImpl::GetUpdateMinTime(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_UpdateMinTime.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentTemperatureIntfControllerImpl::GetUpdateMinTimePropertyCB, context);
    return status;
}

void CurrentTemperatureIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_CurrentValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnCurrentValueChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_Precision.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnPrecisionChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_UpdateMinTime.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnUpdateMinTimeChanged(obj.GetPath(), value);
            }
        }
    }
}

void CurrentTemperatureIntfControllerImpl::GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetCurrentValue(status, obj->GetPath(), val, context);
}

void CurrentTemperatureIntfControllerImpl::GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetPrecision(status, obj->GetPath(), val, context);
}

void CurrentTemperatureIntfControllerImpl::GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetUpdateMinTime(status, obj->GetPath(), val, context);
}

} //namespace services
} //namespace ajn
