/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "OnControlIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* OnControlIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new OnControlIntfControlleeImpl(busAttachment, dynamic_cast<OnControlIntfControlleeListener&>(listener), cdmBusObject);
}

OnControlIntfControlleeImpl::OnControlIntfControlleeImpl(BusAttachment& busAttachment, OnControlIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

OnControlIntfControlleeImpl::~OnControlIntfControlleeImpl()
{
}

QStatus OnControlIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_SwitchOn.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&OnControlIntfControlleeImpl::OnSwitchOn);

    m_methodHandlers.push_back(make_pair(member, methodHandler));

    return status;
}

QStatus OnControlIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

QStatus OnControlIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    // This interface doesn't have any property.
    status = ER_BUS_NO_SUCH_PROPERTY;

    return status;
}

void OnControlIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

void OnControlIntfControlleeImpl::OnSwitchOn(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    ErrorCode errorCode = NOT_ERROR;
    status = m_interfaceListener.OnSwitchOn(errorCode);

    if (status == ER_OK) {
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

} //namespace services
} //namespace ajn