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
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControlleeListener.h>

#include "RapidModeIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RapidModeIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new RapidModeIntfControlleeImpl(busAttachment, dynamic_cast<RapidModeIntfControlleeListener&>(listener), cdmBusObject);
}

RapidModeIntfControlleeImpl::RapidModeIntfControlleeImpl(BusAttachment& busAttachment, RapidModeIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_rapidMode(false)
{
}

RapidModeIntfControlleeImpl::~RapidModeIntfControlleeImpl()
{
}

QStatus RapidModeIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    return status;
}

QStatus RapidModeIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    cout << "On get property. propName: " << propName << endl;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if(!s_prop_RapidMode.compare(propName)) {
                bool rapidMode;
                status = m_interfaceListener.OnGetRapidMode(rapidMode);
                if(status != ER_OK) {
                    QCC_LogError(status, ("%s: failed to get property.",__func__));
                    rapidMode = GetRapidMode();
                }
                else
                {
                    //update internal value;
                    SetRapidMode(rapidMode);
                }
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = rapidMode;
            }
            else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if(!s_prop_RapidMode.compare(propName)) {
                bool rapidMode = GetRapidMode();
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = rapidMode;
            }
            else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus RapidModeIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if(!s_prop_RapidMode.compare(propName)){
        if(val.typeId != ALLJOYN_BOOLEAN) {
            status = ER_BUS_BAD_VALUE_TYPE;
            return status;
        }
        bool rapidMode;
        status = val.Get("b", &rapidMode);
        if(status != ER_OK) {
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
            return status;
        }
        status = m_interfaceListener.OnSetRapidMode(rapidMode);
        if(status != ER_OK) {
            status = ER_INVALID_DATA;
            QCC_LogError(status, ("%s: property value not set ", __func__));
        } else {
            status = SetRapidMode(rapidMode);
        }
    }
    else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void RapidModeIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus RapidModeIntfControlleeImpl::SetRapidMode(const bool rapidMode)
{
    if(m_rapidMode != rapidMode)
    {
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = rapidMode;

        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_RapidMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_rapidMode = rapidMode;
    }
    return ER_OK;
}

} //namespace services
} //namespace ajn