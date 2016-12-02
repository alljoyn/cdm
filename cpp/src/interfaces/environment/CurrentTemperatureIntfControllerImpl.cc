/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "CurrentTemperatureIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CurrentTemperatureIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new CurrentTemperatureIntfControllerImpl(busAttachment, dynamic_cast<CurrentTemperatureIntfControllerListener&>(listener), cdmProxyObject);
}

CurrentTemperatureIntfControllerImpl::CurrentTemperatureIntfControllerImpl(BusAttachment& busAttachment, CurrentTemperatureIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
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

} //namespace services
} //namespace ajn