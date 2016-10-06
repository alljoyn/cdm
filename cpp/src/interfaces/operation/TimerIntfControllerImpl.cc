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
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllerListener.h>

#include "TimerIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TimerIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new TimerIntfControllerImpl(busAttachment, dynamic_cast<TimerIntfControllerListener&>(listener), cdmProxyObject);
}

TimerIntfControllerImpl::TimerIntfControllerImpl(BusAttachment& busAttachment, TimerIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TimerIntfControllerImpl::~TimerIntfControllerImpl()
{
}

QStatus TimerIntfControllerImpl::Init()
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

void TimerIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i)
    {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_ReferenceTimer.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_INT32)
            {
                int32_t level = propValue->v_int32;
                m_interfaceListener.OnReferenceTimerPropertyChanged(obj.GetPath(), level);
            }
        }
        else if (!s_prop_TargetTimeToStart.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_INT32)
            {
                int32_t level = propValue->v_int32;
                m_interfaceListener.OnTargetTimeToStartPropertyChanged(obj.GetPath(), level);
            }
        }
        else if (!s_prop_TargetTimeToStop.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_INT32)
            {
                int32_t level = propValue->v_int32;
                m_interfaceListener.OnTargetTimeToStopPropertyChanged(obj.GetPath(), level);
            }
        }
        else if (!s_prop_RunningTime.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_INT32)
            {
                int32_t level = propValue->v_int32;
                m_interfaceListener.OnRunningTimePropertyChanged(obj.GetPath(), level);
            }
        }
        else if (!s_prop_EstimatedTimeToEnd.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_INT32)
            {
                int32_t level = propValue->v_int32;
                m_interfaceListener.OnEstimatedTimeToEndPropertyChanged(obj.GetPath(), level);
            }
        }
        else if (!s_prop_TargetDuration.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_INT32)
            {
                int32_t level = propValue->v_int32;
                m_interfaceListener.OnTargetDurationPropertyChanged(obj.GetPath(), level);
            }
        }
    }
}

QStatus TimerIntfControllerImpl::GetReferenceTimer(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_ReferenceTimer.c_str(),this, (CdmProxyBusObject::Listener::GetPropertyCB)&TimerIntfControllerImpl::GetReferenceTimerCB,context);

    return status;
}

QStatus TimerIntfControllerImpl::GetTargetTimeToStart(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetTimeToStart.c_str(),this, (CdmProxyBusObject::Listener::GetPropertyCB)&TimerIntfControllerImpl::GetTargetTimeToStartCB,context);

    return status;
}

QStatus TimerIntfControllerImpl::GetTargetTimeToStop(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetTimeToStop.c_str(),this, (CdmProxyBusObject::Listener::GetPropertyCB)&TimerIntfControllerImpl::GetTargetTimeToStopCB,context);

    return status;
}

QStatus TimerIntfControllerImpl::GetEstimatedTimeToEnd(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_EstimatedTimeToEnd.c_str(),this, (CdmProxyBusObject::Listener::GetPropertyCB)&TimerIntfControllerImpl::GetEstimatedTimeToEndCB,context);

    return status;
}

QStatus TimerIntfControllerImpl::GetRunningTime(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_RunningTime.c_str(),this, (CdmProxyBusObject::Listener::GetPropertyCB)&TimerIntfControllerImpl::GetRunningTimeCB,context);

    return status;
}

QStatus TimerIntfControllerImpl::GetTargetDuration(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetDuration.c_str(),this, (CdmProxyBusObject::Listener::GetPropertyCB)&TimerIntfControllerImpl::GetTargetDurationCB,context);

    return status;
}

QStatus TimerIntfControllerImpl::SetTargetTimeToStart(int32_t time, void* context )
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].typeId = ALLJOYN_INT32;
    args[0].v_int32 = time;
    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_SetTargetTimeToStart.c_str(), this, (MessageReceiver::ReplyHandler)&TimerIntfControllerImpl::SetTargetTimeToStartReplyHandler, args, 1, context);

    return status;

}

QStatus TimerIntfControllerImpl::SetTargetTimeToStop(int32_t time, void* context )
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].typeId = ALLJOYN_INT32;
    args[0].v_int32 = time;
    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_SetTargetTimeToStop.c_str(), this, (MessageReceiver::ReplyHandler)&TimerIntfControllerImpl::SetTargetTimeToStopReplyHandler, args, 1, context);

    return status;
}

void TimerIntfControllerImpl::GetReferenceTimerCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    int32_t time;
    value.Get("i",&time);

    m_interfaceListener.OnResponseGetReferenceTimer(status,obj->GetPath().c_str(),time,context);

}
void TimerIntfControllerImpl::GetTargetTimeToStartCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    int32_t time;
    value.Get("i",&time);

    m_interfaceListener.OnResponseGetTargetTimeToStart(status,obj->GetPath().c_str(),time,context);
}
void TimerIntfControllerImpl::GetTargetTimeToStopCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    int32_t time;
    value.Get("i",&time);

    m_interfaceListener.OnResponseGetTargetTimeToStop(status,obj->GetPath().c_str(),time,context);
}
void TimerIntfControllerImpl::GetEstimatedTimeToEndCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    int32_t time;
    value.Get("i",&time);

    m_interfaceListener.OnResponseGetEstimatedTimeToEnd(status,obj->GetPath().c_str(),time,context);
}
void TimerIntfControllerImpl::GetRunningTimeCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    int32_t time;
    value.Get("i",&time);

    m_interfaceListener.OnResponseGetRunningTime(status,obj->GetPath().c_str(),time,context);
}
void TimerIntfControllerImpl::GetTargetDurationCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    int32_t time;
    value.Get("i",&time);

    m_interfaceListener.OnResponseGetTargetDuration(status,obj->GetPath().c_str(),time,context);
}

void TimerIntfControllerImpl::SetTargetTimeToStartReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }
    m_interfaceListener.OnResponseSetTargetTimerToStart(status, m_proxyObject.GetPath(), context, errorName, errorMessage.c_str());
}
void TimerIntfControllerImpl::SetTargetTimeToStopReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }
    m_interfaceListener.OnResponseSetTargetTimerToStop(status, m_proxyObject.GetPath(), context, errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn