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
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "TargetHumidityIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TargetHumidityIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new TargetHumidityIntfControllerImpl(busAttachment, dynamic_cast<TargetHumidityIntfControllerListener&>(listener), cdmProxyObject);
}

TargetHumidityIntfControllerImpl::TargetHumidityIntfControllerImpl(BusAttachment& busAttachment, TargetHumidityIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TargetHumidityIntfControllerImpl::~TargetHumidityIntfControllerImpl()
{
}

QStatus TargetHumidityIntfControllerImpl::Init()
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

void TargetHumidityIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
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
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnTargetValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_MinValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnMinValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_MaxValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnMaxValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_StepValue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnStepValueChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_SelectableHumidityLevels.compare(propNameStr)) {
            if(propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                HumidityLevels levels;
                for (size_t i = 0; i < numVals; ++i)
                    levels.push_back(vals[i]);
                m_interfaceListener.OnSelectableHumidityLevelsChanged(obj.GetPath(), levels);
            }
        }
    }
}

QStatus TargetHumidityIntfControllerImpl::GetTargetValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetHumidityIntfControllerImpl::GetTargetValuePropertyCB, context);
    return status;
}

QStatus TargetHumidityIntfControllerImpl::SetTargetValue(const uint8_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetValue.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&TargetHumidityIntfControllerImpl::SetTargetValuePropertyCB, context);
    return status;
}

QStatus TargetHumidityIntfControllerImpl::GetMinValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MinValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetHumidityIntfControllerImpl::GetMinValuePropertyCB, context);
    return status;
}

QStatus TargetHumidityIntfControllerImpl::GetMaxValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetHumidityIntfControllerImpl::GetMaxValuePropertyCB, context);
    return status;
}

QStatus TargetHumidityIntfControllerImpl::GetStepValue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_StepValue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetHumidityIntfControllerImpl::GetStepValuePropertyCB, context);
    return status;
}

QStatus TargetHumidityIntfControllerImpl::GetSelectableHumidityLevels(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SelectableHumidityLevels.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetHumidityIntfControllerImpl::GetSelectableHumidityLevelsPropertyCB, context);
    return status;
}

void TargetHumidityIntfControllerImpl::SetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetTargetValue(status, obj->GetPath(), context);
}

void TargetHumidityIntfControllerImpl::GetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetTargetValue(status, obj->GetPath(), val, context);
}

void TargetHumidityIntfControllerImpl::GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMinValue(status, obj->GetPath(), val, context);
}

void TargetHumidityIntfControllerImpl::GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMaxValue(status, obj->GetPath(), val, context);
}

void TargetHumidityIntfControllerImpl::GetStepValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetStepValue(status, obj->GetPath(), val, context);
}

void TargetHumidityIntfControllerImpl::GetSelectableHumidityLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    HumidityLevels levels;
    for (size_t i = 0; i < numVals; ++i)
        levels.push_back(vals[i]);
    m_interfaceListener.OnResponseGetSelectableHumidityLevels(status, obj->GetPath(), levels, context);
}

} //namespace services
} //namespace ajn