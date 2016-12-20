/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "ChannelIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ChannelIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new ChannelIntfControlleeImpl(busAttachment, static_cast<ChannelIntfControlleeListener&>(listener), cdmBusObject);
}

ChannelIntfControlleeImpl::ChannelIntfControlleeImpl(BusAttachment& busAttachment, ChannelIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_totalNumberOfChannels(0)
{
}

ChannelIntfControlleeImpl::~ChannelIntfControlleeImpl()
{
}

QStatus ChannelIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_GetChannelList.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&ChannelIntfControlleeImpl::OnGetChannelList);

    m_methodHandlers.push_back(make_pair(member, methodHandler));
    return status;
}

QStatus ChannelIntfControlleeImpl::SetChannelId(const qcc::String& channelId)
{
    if (m_channelId != channelId) {
        MsgArg val;
        val.typeId = ALLJOYN_STRING;
        val.v_string.str = channelId.c_str();
        val.v_string.len = channelId.size();
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ChannelId.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_channelId = channelId;
    }
    return ER_OK;
}

QStatus ChannelIntfControlleeImpl::SetTotalNumberOfChannels(const uint16_t totalNumberOfChannels)
{
    if (m_totalNumberOfChannels != totalNumberOfChannels) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = totalNumberOfChannels;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TotalNumberOfChannels.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_totalNumberOfChannels = totalNumberOfChannels;
    }
    return ER_OK;
}

QStatus ChannelIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_ChannelId.compare(propName))) {
                qcc::String channelId;
                status = m_interfaceListener.OnGetChannelId(channelId);
                if (status != ER_OK) {
                    channelId = GetChannelId();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetChannelId(channelId); // update the value in ChannelIntfControllee.
                }
                status = val.Set("s", channelId.c_str());
                if(status != ER_OK)
                    QCC_LogError(status, ("%s: Failed to set val", __func__));
                val.Stabilize();
            } else if (!(s_prop_TotalNumberOfChannels.compare(propName))) {
                uint16_t totalNumberOfChannels;
                status = m_interfaceListener.OnGetTotalNumberOfChannels(totalNumberOfChannels);
                if (status != ER_OK) {
                    totalNumberOfChannels = GetTotalNumberOfChannels();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetTotalNumberOfChannels(totalNumberOfChannels); // update the value in ChannelIntfControllee.
                }
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = totalNumberOfChannels;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_ChannelId.compare(propName))) {
                const qcc::String channelId = GetChannelId();
                status = val.Set("s", channelId.c_str());
                if(status != ER_OK)
                    QCC_LogError(status, ("%s: Failed to set val", __func__));
                val.Stabilize();            
            } else if (!(s_prop_TotalNumberOfChannels.compare(propName))) {
                const uint16_t totalNumberOfChannels = GetTotalNumberOfChannels();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = totalNumberOfChannels;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus ChannelIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_ChannelId.compare(propName))) {
        if (val.typeId != ALLJOYN_STRING) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        qcc::String channelId = val.v_string.str;
        status = m_interfaceListener.OnSetChannelId(channelId);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetChannelId(channelId); // update the value in ChannelIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void ChannelIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

void ChannelIntfControlleeImpl::OnGetChannelList(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 2) {
        uint16_t startingRecord = args[0].v_uint16;
        uint16_t numRecords = args[1].v_uint16;
        ChannelInterface::ChannelInfoRecords listOfChannelInfoRecords;
        ErrorCode errorCode = NOT_ERROR;

        status = m_interfaceListener.OnGetChannelList(startingRecord, numRecords, listOfChannelInfoRecords, errorCode);
        if (status == ER_OK) {
            int numReturned = listOfChannelInfoRecords.size();
            ChannelInterface::ChannelInfoRecords::const_iterator citer;
            MsgArg* args = new MsgArg[numReturned];
            MsgArg retArgs[1];
            int i = 0;

            for (citer = listOfChannelInfoRecords.begin(); citer != listOfChannelInfoRecords.end(); citer++, i++) {
                status = args[i].Set("(sss)", citer->channelId.c_str(), citer->channelNumber.c_str(), citer->channelName.c_str());
                args[i].Stabilize();
            }
            status = retArgs[0].Set("a(sss)", i, args);

            status = m_busObject.ReplyMethodCall(msg, retArgs, ArraySize(retArgs));
            delete[] args;
        } else {
            if (errorCode == NOT_ERROR) {
                QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                m_busObject.ReplyMethodCall(msg, status);
            } else {
                m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(errorCode).c_str(),
                                            CdmInterface::GetInterfaceErrorMessage(errorCode).c_str());
            }
        }
    } else {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}

QStatus ChannelIntfControlleeImpl::EmitChannelListChanged()
{
    const InterfaceDescription::Member* member = GetInterfaceDescription()->GetMember(s_signal_ChannelListChanged.c_str());
    assert(member);
    return m_busObject.Signal(NULL, SESSION_ID_ALL_HOSTED, *member, NULL, 0, 0);
}

} //namespace services
} //namespace ajn