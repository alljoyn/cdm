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
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "MoistureOutputLevelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* MoistureOutputLevelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new MoistureOutputLevelIntfControllerImpl(busAttachment, dynamic_cast<MoistureOutputLevelIntfControllerListener&>(listener), cdmProxyObject);
}

MoistureOutputLevelIntfControllerImpl::MoistureOutputLevelIntfControllerImpl(BusAttachment& busAttachment, MoistureOutputLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

MoistureOutputLevelIntfControllerImpl::~MoistureOutputLevelIntfControllerImpl()
{
}

QStatus MoistureOutputLevelIntfControllerImpl::Init()
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

void MoistureOutputLevelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_MoistureOutputLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnMoistureOutputLevelChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_MaxMoistureOutputLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnMaxMoistureOutputLevelChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_AutoMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnAutoModeChanged(obj.GetPath(), value);
            }
        }
    }
}

QStatus MoistureOutputLevelIntfControllerImpl::GetMoistureOutputLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MoistureOutputLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&MoistureOutputLevelIntfControllerImpl::GetMoistureOutputLevelPropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfControllerImpl::SetMoistureOutputLevel(const uint8_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_MoistureOutputLevel.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&MoistureOutputLevelIntfControllerImpl::SetMoistureOutputLevelPropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfControllerImpl::GetMaxMoistureOutputLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxMoistureOutputLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&MoistureOutputLevelIntfControllerImpl::GetMaxMoistureOutputLevelPropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfControllerImpl::GetAutoMode(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_AutoMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&MoistureOutputLevelIntfControllerImpl::GetAutoModePropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfControllerImpl::SetAutoMode(const uint8_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_AutoMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&MoistureOutputLevelIntfControllerImpl::SetAutoModePropertyCB, context);
    return status;
}

void MoistureOutputLevelIntfControllerImpl::SetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetMoistureOutputLevel(status, obj->GetPath(), context);
}

void MoistureOutputLevelIntfControllerImpl::GetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMoistureOutputLevel(status, obj->GetPath(), val, context);
}

void MoistureOutputLevelIntfControllerImpl::GetMaxMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMaxMoistureOutputLevel(status, obj->GetPath(), val, context);
}

void MoistureOutputLevelIntfControllerImpl::SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetAutoMode(status, obj->GetPath(), context);
}

void MoistureOutputLevelIntfControllerImpl::GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetAutoMode(status, obj->GetPath(), val, context);
}

} //namespace services
} //namespace ajn