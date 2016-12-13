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
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControlleeListener.h>

#include "ClosedStatusIntfControlleeImpl.h"
#include <alljoyn/cdm/CdmBusObject.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ClosedStatusIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new ClosedStatusIntfControlleeImpl(busAttachment, dynamic_cast<ClosedStatusIntfControlleeListener&>(listener), cdmBusObject);
}

ClosedStatusIntfControlleeImpl::ClosedStatusIntfControlleeImpl(BusAttachment& busAttachment, ClosedStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_isClosed(true)
{
}

ClosedStatusIntfControlleeImpl::~ClosedStatusIntfControlleeImpl()
{
}

QStatus ClosedStatusIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}
QStatus ClosedStatusIntfControlleeImpl::SetIsClosed(const bool isClosed)
{
    if (m_isClosed!= isClosed) {
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = isClosed;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_IsClosed.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_isClosed= isClosed;
    }
    return ER_OK;

}
QStatus ClosedStatusIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
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
            if(!s_prop_IsClosed.compare(propName))
            {
                bool isClosed;
                status = m_interfaceListener.OnGetIsClosed(isClosed);
                if (status != ER_OK)
                {
                    isClosed = GetIsClosed();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                }
                else
                {
                    SetIsClosed(isClosed);
                }
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = isClosed;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
        else
        {
            if (!(s_prop_IsClosed.compare(propName)))
            {
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = GetIsClosed();
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }
    return status;
}

QStatus ClosedStatusIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void ClosedStatusIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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


} //namespace services
} //namespace ajn