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
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControlleeListener.h>

#include "TimerIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TimerIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new TimerIntfControlleeImpl(busAttachment, dynamic_cast<TimerIntfControlleeListener&>(listener), cdmBusObject);
}

TimerIntfControlleeImpl::TimerIntfControlleeImpl(BusAttachment& busAttachment, TimerIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_referenceTimer(0),
    m_targetTimeToStart(0),
    m_targetTimeToStop(0),
    m_estimatedTimeToEnd(0),
    m_runningTime(0),
    m_targetDuration(0)
{
}

TimerIntfControlleeImpl::~TimerIntfControlleeImpl()
{
}

QStatus TimerIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* memberStart = m_interfaceDescription->GetMember(s_method_SetTargetTimeToStart.c_str());
    MessageReceiver::MethodHandler methodHandlerStart = static_cast<MessageReceiver::MethodHandler>(&TimerIntfControlleeImpl::OnSetTargetTimeToStart);

    m_methodHandlers.push_back(make_pair(memberStart, methodHandlerStart));

    const InterfaceDescription::Member* memberStop = m_interfaceDescription->GetMember(s_method_SetTargetTimeToStop.c_str());
    MessageReceiver::MethodHandler methodHandlerStop = static_cast<MessageReceiver::MethodHandler>(&TimerIntfControlleeImpl::OnSetTargetTimeToStop);

    m_methodHandlers.push_back(make_pair(memberStop, methodHandlerStop));

    return status;
}

QStatus TimerIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName)))
    {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    }
    else
    {
        if (s_retrievingActualPropertyValue)
        {
            if(!s_prop_ReferenceTimer.compare(propName))
            {

                int32_t time;
                status = m_interfaceListener.GetReferenceTimer(time);
                if(status != ER_OK)
                {
                    time = GetReferenceTimer();
                    QCC_LogError(status, ("%s: Failed to get property", __func__));
                }
                else
                {
                    SetReferenceTimer(time);
                }
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_TargetTimeToStart.compare(propName))
            {
                int32_t time;
                status = m_interfaceListener.GetTargetTimeToStart(time);
                if(status != ER_OK)
                {
                    time = GetTargetTimeToStart();
                    QCC_LogError(status, ("%s: Failed to get property", __func__));
                }
                else
                {
                }
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_TargetTimeToStop.compare(propName))
            {
                int32_t time;
                status = m_interfaceListener.GetTargetTimeToStop(time);
                if(status != ER_OK)
                {
                    time = GetTargetTimeToStop();
                    QCC_LogError(status, ("%s: Failed to get property", __func__));
                }
                else
                {
                    time = 0;
                }
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_RunningTime.compare(propName))
            {
                int32_t time;
                status = m_interfaceListener.GetRunningTime(time);
                if(status != ER_OK)
                {
                    time = GetRunningTime();
                    QCC_LogError(status, ("%s: Failed to get property", __func__));
                }
                else
                {
                    time = 0;
                }
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_TargetDuration.compare(propName))
            {
                int32_t time;
                status = m_interfaceListener.GetTargetDuration(time);
                if(status != ER_OK)
                {
                    time = GetTargetDuration();
                    QCC_LogError(status, ("%s: Failed to get property", __func__));
                }
                else
                {
                    SetTargetDuration(time);
                }
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_EstimatedTimeToEnd.compare(propName))
            {
                int32_t time;
                status = m_interfaceListener.GetEstimatedTimeToEnd(time);
                if(status != ER_OK)
                {
                    time = GetEstimatedTimeToEnd();
                    QCC_LogError(status, ("%s: Failed to get property", __func__));
                }
                else
                {
                    SetEstimatedTimeToEnd(time);
                }
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
        else
        {
            if(!s_prop_ReferenceTimer.compare(propName))
            {
                int32_t time = GetReferenceTimer();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_TargetTimeToStart.compare(propName))
            {
                int32_t time = GetTargetTimeToStart();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_TargetTimeToStop.compare(propName))
            {
                int32_t time = GetTargetTimeToStop();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_RunningTime.compare(propName))
            {
                int32_t time = GetRunningTime();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_TargetDuration.compare(propName))
            {
                int32_t time = GetTargetDuration();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else if (!s_prop_EstimatedTimeToEnd.compare(propName))
            {
                int32_t time = GetEstimatedTimeToEnd();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = time;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }
    return status;
}

QStatus TimerIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void TimerIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}


QStatus TimerIntfControlleeImpl::SetReferenceTimer(const int32_t time)
{
    if(m_referenceTimer != time)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_INT32;
        arg.v_int32 = time;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ReferenceTimer.c_str(), arg,SESSION_ID_ALL_HOSTED,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_referenceTimer = time;
        UpdateProperties();
    }
    return ER_OK;
}
QStatus TimerIntfControlleeImpl::SetTargetTimeToStart(const int32_t time)
{
    if(m_targetTimeToStart != time)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_INT32;
        arg.v_int32 = time;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetTimeToStart.c_str(), arg,SESSION_ID_ALL_HOSTED,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_targetTimeToStart = time;
        UpdateProperties();
    }
    return ER_OK;
}

QStatus TimerIntfControlleeImpl::SetTargetTimeToStop(const int32_t time)
{
    if(m_targetTimeToStop != time)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_INT32;
        arg.v_int32 = time;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetTimeToStop.c_str(), arg,SESSION_ID_ALL_HOSTED,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_targetTimeToStop = time;
        UpdateProperties();
    }
    return ER_OK;
}

QStatus TimerIntfControlleeImpl::SetEstimatedTimeToEnd(const int32_t time)
{
   if(m_estimatedTimeToEnd != time)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_INT32;
        arg.v_int32 = time;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_EstimatedTimeToEnd.c_str(), arg,SESSION_ID_ALL_HOSTED,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_estimatedTimeToEnd = time;
    }
    return ER_OK;
}

QStatus TimerIntfControlleeImpl::SetRunningTime(const int32_t time)
{
    if(m_runningTime != time)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_INT32;
        arg.v_int32 = time;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_RunningTime.c_str(), arg,SESSION_ID_ALL_HOSTED,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_runningTime = time;
    }
    return ER_OK;
}

QStatus TimerIntfControlleeImpl::SetTargetDuration(const int32_t time)
{
    if(m_targetDuration != time)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_INT32;
        arg.v_int32 = time;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetDuration.c_str(), arg,SESSION_ID_ALL_HOSTED,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_targetDuration = time;
    }
    return ER_OK;
}

void TimerIntfControlleeImpl::OnSetTargetTimeToStart(const InterfaceDescription::Member* member, Message& msg)
{
    cout << "TimerIntfControlleeImpl::OnSetTargetTimeToStart" << endl;
    QStatus status = ER_OK;

    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1)
    {
        if(args[0].typeId != ALLJOYN_INT32) {
            m_busObject.ReplyMethodCall(msg, ER_BAD_ARG_1);
        }
        int32_t time = args[0].v_int32;
        ErrorCode errorCode = NOT_ERROR;
        status = m_interfaceListener.OnSetTargetTimeToStart(time, errorCode);
        if (status == ER_OK) {
            status = SetTargetTimeToStart(time); //update internal value
            m_busObject.ReplyMethodCall(msg, status);
        } else {
            if (errorCode == NOT_ERROR) {
                QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                m_busObject.ReplyMethodCall(msg, status);
            } else {
                    m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(errorCode).c_str(),
                            CdmInterface::GetInterfaceErrorMessage(errorCode).c_str());
            }
        }
    }
    else
    {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}
void TimerIntfControlleeImpl::OnSetTargetTimeToStop(const InterfaceDescription::Member* member, Message& msg)
{
    cout << "TimerIntfControlleeImpl::OnSetTargetTimeToStop" << endl;
    QStatus status = ER_OK;

    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1)
    {
        if(args[0].typeId != ALLJOYN_INT32) {
            m_busObject.ReplyMethodCall(msg, ER_BAD_ARG_1);
        }
        int32_t time = args[0].v_int32;
        ErrorCode errorCode = NOT_ERROR;
        status = m_interfaceListener.OnSetTargetTimeToStop(time, errorCode);
        if (status == ER_OK) {
            status = SetTargetTimeToStop(time); //update internal value
            m_busObject.ReplyMethodCall(msg, status);
        } else {
            if (errorCode == NOT_ERROR) {
                QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                m_busObject.ReplyMethodCall(msg, status);
            } else {
                    m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(errorCode).c_str(),
                            CdmInterface::GetInterfaceErrorMessage(errorCode).c_str());
            }
        }
    }
    else
    {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}
void TimerIntfControlleeImpl::UpdateProperties()
{
    int32_t estimatedTimeToEnd = 0;
    int32_t runningTime = 0;
    int32_t targetDuration = 0;

    //recalculate timer values
    if(m_referenceTimer < m_targetTimeToStart)
    {
        estimatedTimeToEnd = m_targetTimeToStop - m_targetTimeToStart;
        runningTime = 0;
    }
    else if(m_referenceTimer >= m_targetTimeToStart && m_referenceTimer <= m_targetTimeToStop)
    {
        estimatedTimeToEnd = m_targetTimeToStop - m_referenceTimer;
        runningTime = m_referenceTimer - m_targetTimeToStart;
    }
    else
    {
        estimatedTimeToEnd = 0;
        runningTime = m_targetTimeToStop - m_targetTimeToStart;
    }

    if(m_targetTimeToStart > 0 &&  m_targetTimeToStop > 0)
    {
        targetDuration = m_targetTimeToStop - m_targetTimeToStart;
    }

    this->SetEstimatedTimeToEnd(estimatedTimeToEnd);
    this->SetRunningTime(runningTime);
    this->SetTargetDuration(targetDuration);

}

} //namespace services
} //namespace ajn