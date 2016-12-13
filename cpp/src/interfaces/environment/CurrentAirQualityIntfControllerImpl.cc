/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllerListener.h>

#include "CurrentAirQualityIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CurrentAirQualityIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new CurrentAirQualityIntfControllerImpl(busAttachment, dynamic_cast<CurrentAirQualityIntfControllerListener&>(listener), cdmProxyObject);
}

CurrentAirQualityIntfControllerImpl::CurrentAirQualityIntfControllerImpl(BusAttachment& busAttachment, CurrentAirQualityIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

CurrentAirQualityIntfControllerImpl::~CurrentAirQualityIntfControllerImpl()
{
}

QStatus CurrentAirQualityIntfControllerImpl::Init()
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

void CurrentAirQualityIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
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
                m_interfaceListener.OnContaminantTypeChanged(obj.GetPath(), value);
            }
        }
        else if (!s_prop_CurrentValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnCurrentValueChanged(obj.GetPath(), value);
            }
        }
        else if (!s_prop_MaxValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnMaxValueChanged(obj.GetPath(), value);
            }
        }
        else if (!s_prop_MinValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double value = propValue->v_double;
                m_interfaceListener.OnMinValueChanged(obj.GetPath(), value);
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

void CurrentAirQualityIntfControllerImpl::GetContaminantTypePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetContaminantType(status, obj->GetPath(), val, context);
}

void CurrentAirQualityIntfControllerImpl::GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetCurrentValue(status, obj->GetPath(), val, context);
}

void CurrentAirQualityIntfControllerImpl::GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetMaxValue(status, obj->GetPath(), val, context);
}

void CurrentAirQualityIntfControllerImpl::GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetMinValue(status, obj->GetPath(), val, context);
}


void CurrentAirQualityIntfControllerImpl::GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetPrecision(status, obj->GetPath(), val, context);
}

void CurrentAirQualityIntfControllerImpl::GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetUpdateMinTime(status, obj->GetPath(), val, context);
}

QStatus CurrentAirQualityIntfControllerImpl::GetContaminantType(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_ContaminantType.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityIntfControllerImpl::GetContaminantTypePropertyCB, context);
    return status;
}

QStatus CurrentAirQualityIntfControllerImpl::GetCurrentValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_CurrentValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityIntfControllerImpl::GetCurrentValuePropertyCB, context);
    return status;
}

QStatus CurrentAirQualityIntfControllerImpl::GetMaxValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityIntfControllerImpl::GetMaxValuePropertyCB, context);
    return status;
}

QStatus CurrentAirQualityIntfControllerImpl::GetMinValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MinValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityIntfControllerImpl::GetMinValuePropertyCB, context);
    return status;
}

QStatus CurrentAirQualityIntfControllerImpl::GetPrecision(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Precision.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityIntfControllerImpl::GetPrecisionPropertyCB, context);
    return status;
}

QStatus CurrentAirQualityIntfControllerImpl::GetUpdateMinTime(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_UpdateMinTime.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CurrentAirQualityIntfControllerImpl::GetUpdateMinTimePropertyCB, context);
    return status;
}


} //namespace services
} //namespace ajn