/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "FanSpeedLevelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* FanSpeedLevelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new FanSpeedLevelIntfControllerImpl(busAttachment, dynamic_cast<FanSpeedLevelIntfControllerListener&>(listener), cdmProxyObject);
}

FanSpeedLevelIntfControllerImpl::FanSpeedLevelIntfControllerImpl(BusAttachment& busAttachment, FanSpeedLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

FanSpeedLevelIntfControllerImpl::~FanSpeedLevelIntfControllerImpl()
{
}

QStatus FanSpeedLevelIntfControllerImpl::Init()
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

void FanSpeedLevelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_FanSpeedLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnFanSpeedLevelChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_AutoMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnAutoModeChanged(obj.GetPath(), value);
            }
        }
    }
}


QStatus FanSpeedLevelIntfControllerImpl::GetFanSpeedLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_FanSpeedLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FanSpeedLevelIntfControllerImpl::GetFanSpeedLevelPropertyCB, context);
    return status;
}

QStatus FanSpeedLevelIntfControllerImpl::SetFanSpeedLevel(const uint8_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_FanSpeedLevel.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&FanSpeedLevelIntfControllerImpl::SetFanSpeedLevelPropertyCB, context);
    return status;
}

QStatus FanSpeedLevelIntfControllerImpl::GetMaxFanSpeedLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxFanSpeedLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FanSpeedLevelIntfControllerImpl::GetMaxFanSpeedLevelPropertyCB, context);
    return status;
}


QStatus FanSpeedLevelIntfControllerImpl::GetAutoMode(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_AutoMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FanSpeedLevelIntfControllerImpl::GetAutoModePropertyCB, context);
    return status;
}


QStatus FanSpeedLevelIntfControllerImpl::SetAutoMode(const uint8_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_AutoMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&FanSpeedLevelIntfControllerImpl::SetAutoModePropertyCB, context);
    return status;
}


void FanSpeedLevelIntfControllerImpl::SetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetFanSpeedLevel(status, obj->GetPath(), context);
}

void FanSpeedLevelIntfControllerImpl::GetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetFanSpeedLevel(status, obj->GetPath(), val, context);
}

void FanSpeedLevelIntfControllerImpl::GetMaxFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMaxFanSpeedLevel(status, obj->GetPath(), val, context);
}

void FanSpeedLevelIntfControllerImpl::SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetAutoMode(status, obj->GetPath(), context);
}

void FanSpeedLevelIntfControllerImpl::GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
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