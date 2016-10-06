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
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "TargetTemperatureLevelIntfControlleeImpl.h"
#include <cmath>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {


CdmInterface* TargetTemperatureLevelIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new TargetTemperatureLevelIntfControlleeImpl(busAttachment, static_cast<TargetTemperatureLevelIntfControlleeListener&>(listener), cdmBusObject);
}


TargetTemperatureLevelIntfControlleeImpl::TargetTemperatureLevelIntfControlleeImpl(BusAttachment& busAttachment, TargetTemperatureLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_TargetLevel(0),
    m_MaxLevel(100)
{
}

TargetTemperatureLevelIntfControlleeImpl::~TargetTemperatureLevelIntfControlleeImpl()
{
}

QStatus TargetTemperatureLevelIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus TargetTemperatureLevelIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;


    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_TargetLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetTargetLevel(value);
                if (status != ER_OK) {
                    value = GetTargetLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetTargetLevel(value); // update TargetValue in TargetTemperatureLevelIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMaxLevel(value);
                if (status != ER_OK) {
                    value = GetMaxLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxLevel(value); // update MaxValue in TargetTemperatureLevelIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_SelectableTemperatureLevels.compare(propName))) {
                TargetTemperatureLevelInterface::TemperatureLevels value;
                status = m_interfaceListener.OnGetSelectableTemperatureLevels(value);
                if (status != ER_OK) {
                    value = GetSelectableTemperatureLevels();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetSelectableTemperatureLevels(value); // update StepValue in TargetTemperatureLevelIntfControllee.
                }

                MsgArg* args = new MsgArg[value.size()];

                for(size_t i = 0; i < value.size(); i++) {
                     args[i].Set("y", value[i]);
                     args[i].Stabilize();
                }

                val.Set("ay", value.size(), args);
                val.Stabilize();
                delete[] args;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_TargetLevel.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetTargetLevel();
            } else if(!(s_prop_MaxLevel.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetMaxLevel();
            } else if(!(s_prop_SelectableTemperatureLevels.compare(propName))) {
                TargetTemperatureLevelInterface::TemperatureLevels value = GetSelectableTemperatureLevels();

                uint8_t* vals = new uint8_t[value.size()];
                for(size_t i = 0; i < value.size(); i++) {
                    vals[i] = (uint8_t)value[i];
                }
                val.Set("ay", value.size(), vals);
                val.Stabilize();
                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus TargetTemperatureLevelIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_TargetLevel.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint8_t value = AdjustTargetValue(val.v_byte);
        if (IsValidTargetValue(value)) {
            status = m_interfaceListener.OnSetTargetLevel(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to set property value", __func__));
                status = ER_BUS_PROPERTY_VALUE_NOT_SET;
            } else {
                SetTargetLevel(value); // update the value in TargetTemperatureLevelIntfControllee.
            }
        } else {
            // TODO: Implement org.alljoyn.Error.InvalidValue
            status = ER_INVALID_DATA;
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void TargetTemperatureLevelIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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


QStatus TargetTemperatureLevelIntfControlleeImpl::SetTargetLevel(const uint8_t value)
{
    if (m_TargetLevel == value)
        return ER_OK;

    if (value > m_MaxLevel) {
        QCC_LogError(ER_FAIL, ("%s: TargetTemperatureLevel is out of range. ", __func__));
        return ER_FAIL;
    }

    MsgArg val;
    val.typeId = ALLJOYN_BYTE;
    val.v_byte = value;
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    m_TargetLevel = value;

    return ER_OK;
}

QStatus TargetTemperatureLevelIntfControlleeImpl::SetMaxLevel(const uint8_t value)
{
    if (m_MaxLevel == value)
        return ER_OK;

    MsgArg val;
    val.typeId = ALLJOYN_BYTE;
    val.v_byte = value;
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    m_MaxLevel = value;
    return ER_OK;
}

QStatus TargetTemperatureLevelIntfControlleeImpl::SetSelectableTemperatureLevels(const TemperatureLevels& value)
{
    if (m_SelectableTemperatureLevels.size() == value.size()) {
        bool changed = false;
        for (size_t i = 0; i < value.size(); i++) {
            if (m_SelectableTemperatureLevels[i] != value[i]) {
                changed = true;
                break;
            }
        }
        if (!changed)
            return ER_OK;
    }
    MsgArg val;
    uint8_t* vals = new uint8_t[value.size()];
    for(size_t i = 0; i < value.size(); i++)
    {
        vals[i] = (uint8_t)value[i];
    }
    val.Set("ay", value.size(), vals);
    val.Stabilize();
    delete[] vals;
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SelectableTemperatureLevels.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    m_SelectableTemperatureLevels = value;

    return ER_OK;
}

bool TargetTemperatureLevelIntfControlleeImpl::IsValidTargetValue(uint8_t value) {
    for (size_t i = 0; i < m_SelectableTemperatureLevels.size(); ++i) {
        if (m_SelectableTemperatureLevels[i] == value)
            return true;
    }
    return false;
}

uint8_t TargetTemperatureLevelIntfControlleeImpl::AdjustTargetValue(uint8_t value) {
    return value > m_MaxLevel ? m_MaxLevel : value;
}


} //namespace services
} //namespace ajn