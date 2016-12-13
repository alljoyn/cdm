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
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllerListener.h>

#include "RapidModeTimedIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RapidModeTimedIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new RapidModeTimedIntfControllerImpl(busAttachment, dynamic_cast<RapidModeTimedIntfControllerListener&>(listener), cdmProxyObject);
}

RapidModeTimedIntfControllerImpl::RapidModeTimedIntfControllerImpl(BusAttachment& busAttachment, RapidModeTimedIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

RapidModeTimedIntfControllerImpl::~RapidModeTimedIntfControllerImpl()
{
}

QStatus RapidModeTimedIntfControllerImpl::Init()
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

void RapidModeTimedIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_RapidModeMinutesRemaining.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnRapidModeMinutesRemainingChanged(obj.GetPath(), value);
            }
        }
    }
}

QStatus RapidModeTimedIntfControllerImpl::GetRapidModeMinutesRemaining(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_RapidModeMinutesRemaining.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&RapidModeTimedIntfControllerImpl::GetRapidModeMinutesRemainingPropertyCB, context);

    return status;
}

QStatus RapidModeTimedIntfControllerImpl::SetRapidModeMinutesRemaining(const uint16_t value, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("q", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_RapidModeMinutesRemaining.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&RapidModeTimedIntfControllerImpl::SetRapidModeMinutesRemainingPropertyCB, context);

    return status;
}

QStatus RapidModeTimedIntfControllerImpl::GetMaxSetMinutes(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxSetMinutes.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&RapidModeTimedIntfControllerImpl::GetMaxSetMinutesPropertyCB, context);

    return status;
}

void RapidModeTimedIntfControllerImpl::GetRapidModeMinutesRemainingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint16_t val;
    value.Get("q", &val);

    m_interfaceListener.OnResponseGetRapidModeMinutesRemaining(status, obj->GetPath(), val, context);
}

void RapidModeTimedIntfControllerImpl::SetRapidModeMinutesRemainingPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetRapidModeMinutesRemaining(status, obj->GetPath(), context);
}


void RapidModeTimedIntfControllerImpl::GetMaxSetMinutesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint16_t val;
    value.Get("q", &val);

    m_interfaceListener.OnResponseGetMaxSetMinutes(status, obj->GetPath(), val, context);
}

} //namespace services
} //namespace ajn