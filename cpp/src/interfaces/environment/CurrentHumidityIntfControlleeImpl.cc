/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "CurrentHumidityIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {


CdmInterface* CurrentHumidityIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new CurrentHumidityIntfControlleeImpl(busAttachment, static_cast<CurrentHumidityIntfControlleeListener&>(listener), cdmBusObject);
}


CurrentHumidityIntfControlleeImpl::CurrentHumidityIntfControlleeImpl(BusAttachment& busAttachment, CurrentHumidityIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_currentValue(0),
    m_maxValue(0)
{
}

CurrentHumidityIntfControlleeImpl::~CurrentHumidityIntfControlleeImpl()
{
}

QStatus CurrentHumidityIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus CurrentHumidityIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;


    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_CurrentValue.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetCurrentValue(value);
                if (status != ER_OK) {
                    value = GetCurrentValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCurrentValue(value); // update the value in CurrentHumidityIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxValue.compare(propName))) {
                uint8_t maxValue;
                status = m_interfaceListener.OnGetMaxValue(maxValue);
                if (status != ER_OK) {
                    maxValue = GetMaxValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxValue(maxValue);  // update the value in CurrentHumidityIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = maxValue;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_CurrentValue.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetCurrentValue();
            } else if (!(s_prop_MaxValue.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetMaxValue();
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus CurrentHumidityIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    return ER_BUS_NO_SUCH_PROPERTY;
}

void CurrentHumidityIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}


QStatus CurrentHumidityIntfControlleeImpl::SetCurrentValue(const uint8_t value)
{
    uint8_t maxVal = GetMaxValue();
    if (value > maxVal)
    {
        QCC_LogError(ER_FAIL, ("%s: CurrentValue is invalid Value. ", __func__));
        return ER_FAIL;
    }
    if (m_currentValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_currentValue = value;
    }

    return ER_OK;
}

QStatus CurrentHumidityIntfControlleeImpl::SetMaxValue(const uint8_t value)
{
    if (value > MAX_HUMIDITY)
    {
        QCC_LogError(ER_FAIL, ("%s: MaxValue is invalid Value. ", __func__));
        return ER_FAIL;
    }
    QStatus status = ER_OK;
    if (m_maxValue != value) {
        m_maxValue = value;
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return status;
}

} //namespace services
} //namespace ajn