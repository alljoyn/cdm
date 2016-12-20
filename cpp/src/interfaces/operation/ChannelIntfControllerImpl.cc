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
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControllerListener.h>

#include "ChannelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ChannelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new ChannelIntfControllerImpl(busAttachment, static_cast<ChannelIntfControllerListener&>(listener), cdmProxyObject);
}

ChannelIntfControllerImpl::ChannelIntfControllerImpl(BusAttachment& busAttachment, ChannelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

ChannelIntfControllerImpl::~ChannelIntfControllerImpl()
{
}

QStatus ChannelIntfControllerImpl::Init()
{
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
        return status;
    }

    const InterfaceDescription* intf = GetInterfaceDescription();
    if (intf) {
        const InterfaceDescription::Member* channelListChanged = intf->GetMember(s_signal_ChannelListChanged.c_str());
        if (channelListChanged) {
            status = m_busAttachment.RegisterSignalHandler(this, static_cast<SignalHandler>(&ChannelIntfControllerImpl::ChannelListChanged), channelListChanged, NULL);
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: RegisterSignalHandler for ChannelListChanged signal failed.", __func__));
            }
        } else {
            status = ER_FAIL;
            QCC_LogError(status, ("%s: ChannelListChaned signal is not exist.", __func__));
        }
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: The interface description is not exist.", __func__));
    }

    return status;
}

QStatus ChannelIntfControllerImpl::SetChannelId(const qcc::String channelId, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("s", channelId.c_str());
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_ChannelId.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&ChannelIntfControllerImpl::SetChannelIdPropertyCB, context);

    return status;
}

QStatus ChannelIntfControllerImpl::GetChannelId(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_ChannelId.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ChannelIntfControllerImpl::GetChannelIdPropertyCB, context);

    return status;
}

QStatus ChannelIntfControllerImpl::GetTotalNumberOfChannels(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TotalNumberOfChannels.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ChannelIntfControllerImpl::GetTotalNumberOfChannelsPropertyCB, context);

    return status;
}

QStatus ChannelIntfControllerImpl::GetChannelList(const uint16_t startingRecord, const uint16_t numRecords, void* context)
{
    QStatus status = ER_OK;

    MsgArg args[2];
    args[0].Set("q", startingRecord);
    args[1].Set("q", numRecords);

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_GetChannelList.c_str(), this, (MessageReceiver::ReplyHandler)&ChannelIntfControllerImpl::GetChannelListReplyHandler, args, 2, context);

    return status;
}
void ChannelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_ChannelId.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_STRING) {
                String channelId = String(propValue->v_string.str);
                m_interfaceListener.OnChannelIdChanged(obj.GetPath(), channelId);
            }
        } else if (!s_prop_TotalNumberOfChannels.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t totalNumberOfChannels = propValue->v_uint16;
                m_interfaceListener.OnTotalNumberOfChannelsChanged(obj.GetPath(), totalNumberOfChannels);
            }
        }
    }
}

void ChannelIntfControllerImpl::SetChannelIdPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetChannelId(status, obj->GetPath(), context);
}

void ChannelIntfControllerImpl::GetChannelIdPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    const char* id;
    value.Get("s", &id);
    String channelId = String(id);

    m_interfaceListener.OnResponseGetChannelId(status, obj->GetPath(), channelId, context);
}

void ChannelIntfControllerImpl::GetTotalNumberOfChannelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint16_t totalNumberOfChannels;
    value.Get("q", &totalNumberOfChannels);

    m_interfaceListener.OnResponseGetTotalNumberOfChannels(status, obj->GetPath(), totalNumberOfChannels, context);
}

void ChannelIntfControllerImpl::GetChannelListReplyHandler(Message& message, void* context)
{
    ChannelInterface::ChannelInfoRecords records;
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET) {
        status = ER_FAIL;
    } else {
        size_t numArgs;
        const MsgArg* args;
        message->GetArgs(numArgs, args);

        if (!args[0].HasSignature("a(sss)")) {
            return;
        }

        MsgArg* entries;
        size_t numEntries;
        ChannelInterface::ChannelInfoRecord record;

        args[0].Get("a(sss)", &numEntries, &entries);
        for (size_t i = 0; i < numEntries; ++i) {
            const char* channelId, *channelNumber, *channelName;
            entries[i].Get("(sss)", &channelId, &channelNumber, &channelName);
            record.channelId = String(channelId);
            record.channelName = String(channelName);
            record.channelNumber = String(channelNumber);
            records.push_back(record);
        }
    }
    m_interfaceListener.OnResponseGetChannelList(status, m_proxyObject.GetPath(), records, context,
                                                 errorName, errorMessage.c_str());
}

void ChannelIntfControllerImpl::ChannelListChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& message)
{
    String path = String(srcPath);

    m_interfaceListener.OnChannelListChanged(path);
}

} //namespace services
} //namespace ajn