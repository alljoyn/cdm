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

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureIntfControllerListener.h>
#include <alljoyn/hae/HaeProxyBusObject.h>
#include "TargetTemperatureIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* TargetTemperatureIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new TargetTemperatureIntfControllerImpl(busAttachment, dynamic_cast<TargetTemperatureIntfControllerListener&>(listener), haeProxyObject);
}

TargetTemperatureIntfControllerImpl::TargetTemperatureIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TargetTemperatureIntfControllerImpl::~TargetTemperatureIntfControllerImpl()
{
}

QStatus TargetTemperatureIntfControllerImpl::Init()
{
    QStatus status = HaeInterface::Init();
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

void TargetTemperatureIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_TargetValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnTargetValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_MinValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnMinValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_MaxValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnMaxValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_StepValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnStepValueChanged(obj.GetPath(), value);
            }
        }
    }
}

QStatus TargetTemperatureIntfControllerImpl::GetTargetValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureIntfControllerImpl::GetTargetValuePropertyCB, context);
    return status;
}

QStatus TargetTemperatureIntfControllerImpl::SetTargetValue(const double value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("d", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetValue.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&TargetTemperatureIntfControllerImpl::SetTargetValuePropertyCB, context);
    return status;
}

QStatus TargetTemperatureIntfControllerImpl::GetMinValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MinValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureIntfControllerImpl::GetMinValuePropertyCB, context);
    return status;
}

QStatus TargetTemperatureIntfControllerImpl::GetMaxValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureIntfControllerImpl::GetMaxValuePropertyCB, context);
    return status;
}

QStatus TargetTemperatureIntfControllerImpl::GetStepValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_StepValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureIntfControllerImpl::GetStepValuePropertyCB, context);
    return status;
}

void TargetTemperatureIntfControllerImpl::SetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetTargetValue(status, obj->GetPath(), context);
}

void TargetTemperatureIntfControllerImpl::GetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetTargetValue(status, obj->GetPath(), val, context);
}

void TargetTemperatureIntfControllerImpl::GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetMinValue(status, obj->GetPath(), val, context);
}

void TargetTemperatureIntfControllerImpl::GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetMaxValue(status, obj->GetPath(), val, context);
}

void TargetTemperatureIntfControllerImpl::GetStepValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetStepValue(status, obj->GetPath(), val, context);
}

} //namespace services
} //namespace ajn
