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
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "TargetHumidityIntfControlleeImpl.h"
#include <cmath>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {


CdmInterface* TargetHumidityIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new TargetHumidityIntfControlleeImpl(busAttachment, static_cast<TargetHumidityIntfControlleeListener&>(listener), cdmBusObject);
}


TargetHumidityIntfControlleeImpl::TargetHumidityIntfControlleeImpl(BusAttachment& busAttachment, TargetHumidityIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_TargetValue(0),
    m_MinValue(0),
    m_MaxValue(100),
    m_StepValue(1),
    m_currentStrategy(ROUNDING_TO_NEAREST_VALUE)
{
}

TargetHumidityIntfControlleeImpl::~TargetHumidityIntfControlleeImpl()
{
}

QStatus TargetHumidityIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus TargetHumidityIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;


    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_TargetValue.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetTargetValue(value);
                if (status != ER_OK) {
                    value = GetTargetValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetTargetValue(value); // update TargetValue in TargetHumidityIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MinValue.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMinValue(value);
                if (status != ER_OK) {
                    value = GetMinValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMinValue(value); // update MinValue in TargetHumidityIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxValue.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMaxValue(value);
                if (status != ER_OK) {
                    value = GetMaxValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxValue(value); // update MaxValue in TargetHumidityIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_StepValue.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetStepValue(value);
                if (status != ER_OK) {
                    value = GetStepValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetStepValue(value); // update StepValue in TargetHumidityIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_SelectableHumidityLevels.compare(propName))) {
                TargetHumidityInterface::HumidityLevels value;
                status = m_interfaceListener.OnGetSelectableHumidityLevels(value);
                if (status != ER_OK) {
                    value = GetSelectableHumidityLevels();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetSelectableHumidityLevels(value); // update StepValue in TargetHumidityIntfControllee.
                }

                MsgArg* args = new MsgArg[value.size()];
                TargetHumidityInterface::HumidityLevels::const_iterator citer;
                int i=0;

                for(citer = value.begin(); citer != value.end(); citer++, i++) {
                     args[i].Set("y", *citer);
                     args[i].Stabilize();
                }

                val.Set("ay", i, args);
                val.Stabilize();
                delete[] args;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_TargetValue.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetTargetValue();
            } else if(!(s_prop_MinValue.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetMinValue();
            } else if(!(s_prop_MaxValue.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetMaxValue();
            } else if(!(s_prop_StepValue.compare(propName))) {
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = GetStepValue();
            } else if(!(s_prop_SelectableHumidityLevels.compare(propName))) {
                TargetHumidityInterface::HumidityLevels value = GetSelectableHumidityLevels();

                uint8_t* vals = new uint8_t[value.size()];
                for(size_t i = 0; i < value.size(); i++)
                {
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

QStatus TargetHumidityIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_TargetValue.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint8_t value = AdjustTargetValue(val.v_byte);
        if (IsValidTargetValue(value)) {
            status = m_interfaceListener.OnSetTargetValue(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to set property value", __func__));
                status = ER_BUS_PROPERTY_VALUE_NOT_SET;
            } else {
                SetTargetValue(value); // update the value in TargetHumidityIntfControllee.
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

void TargetHumidityIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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


QStatus TargetHumidityIntfControlleeImpl::SetTargetValue(const uint8_t value)
{
    if (!IsValidTargetValue(value)) {
        QCC_LogError(ER_FAIL, ("%s: TargetHumidity is invalid Value. ", __func__));
        return ER_FAIL;
    }

    if (m_TargetValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_TargetValue = value;
    }

    return ER_OK;
}

QStatus TargetHumidityIntfControlleeImpl::SetMinValue(const uint8_t value)
{
    uint8_t maxValue = GetMaxValue();
    if(value > maxValue)
    {
        QCC_LogError(ER_FAIL, ("%s: MinValue is invalid Value. ", __func__));
        return ER_FAIL;
    }
    if (m_MinValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MinValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_MinValue = value;
    }

    return ER_OK;
}

QStatus TargetHumidityIntfControlleeImpl::SetMaxValue(const uint8_t value)
{
    uint8_t minValue = GetMinValue();
    if(value < minValue)
    {
        QCC_LogError(ER_FAIL, ("%s: MaxValue is invalid Value. ", __func__));
        return ER_FAIL;
    }
    if (m_MaxValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_MaxValue = value;
    }

    return ER_OK;
}

QStatus TargetHumidityIntfControlleeImpl::SetStepValue(const uint8_t value)
{
    if (m_StepValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_StepValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_StepValue = value;
    }

    return ER_OK;
}

QStatus TargetHumidityIntfControlleeImpl::SetSelectableHumidityLevels(const HumidityLevels& value)
{
    if (m_SelectableHumidityLevels.size() == value.size()) {
        bool changed = false;
        for (size_t i = 0; i < value.size(); i++) {
            if (m_SelectableHumidityLevels[i] != value[i]) {
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
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SelectableHumidityLevels.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    m_SelectableHumidityLevels = value;

    return ER_OK;
}

QStatus TargetHumidityIntfControlleeImpl::SetStrategyOfAdjustingTargetValue(AdjustStrategy strategy) {
    switch(strategy) {
    case ROUNDING_TO_NEAREST_VALUE:
    case ROUNDING_OFF:
    case ROUNDING_UP:
        return ER_OK;
    default:
        return ER_FAIL;
    }
}

bool TargetHumidityIntfControlleeImpl::IsValidTargetValue(uint8_t value) {
    if (m_MaxValue != m_MinValue) {
        if (value < m_MinValue || value > m_MaxValue) {
            return false;
        }
        if (m_StepValue != 0 && (value - m_MinValue)%m_StepValue != 0) {
            return false;
        }
        return true;
    }

    for (size_t i = 0; i < m_SelectableHumidityLevels.size(); ++i) {
        if (m_SelectableHumidityLevels[i] == value)
            return true;
    }
    return false;
}

uint8_t TargetHumidityIntfControlleeImpl::AdjustTargetValue(uint8_t value) {
    if (m_MaxValue == m_MinValue)
        return value;
    if (m_StepValue == 0)
        return value;

    double div = value/m_StepValue;
    switch(m_currentStrategy) {
    case ROUNDING_OFF:
        value = std::floor(div) * m_StepValue;
        break;
    case ROUNDING_TO_NEAREST_VALUE:
        value = std::floor(div + 0.5) * m_StepValue;
        break;
    case ROUNDING_UP:
        value = std::ceil(div) * m_StepValue;
        break;
    }
    return (value < m_MinValue) ? m_MinValue : (value > m_MaxValue ? m_MaxValue : value);
}


} //namespace services
} //namespace ajn