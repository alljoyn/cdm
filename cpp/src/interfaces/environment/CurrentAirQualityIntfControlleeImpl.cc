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
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControlleeListener.h>

#include "CurrentAirQualityIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CurrentAirQualityIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new CurrentAirQualityIntfControlleeImpl(busAttachment, dynamic_cast<CurrentAirQualityIntfControlleeListener&>(listener), cdmBusObject);
}

CurrentAirQualityIntfControlleeImpl::CurrentAirQualityIntfControlleeImpl(BusAttachment& busAttachment, CurrentAirQualityIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_contaminantType(CurrentAirQualityInterface::CONTAMINANT_TYPE_CH2O),
    m_currentValue(0.0),
    m_maxValue(CurrentAirQualityInterface::DEFAULT_MAX_VALUE),
    m_minValue(CurrentAirQualityInterface::DEFAULT_MIN_VALUE),
    m_precision(0.0),
    m_updateMinTime(0)
{
}

CurrentAirQualityIntfControlleeImpl::~CurrentAirQualityIntfControlleeImpl()
{
}

QStatus CurrentAirQualityIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    return status;
}

QStatus CurrentAirQualityIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_ContaminantType.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetContaminantType(value);
                if (status != ER_OK) {
                    value = GetContaminantType();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetContaminantType(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_CurrentValue.compare(propName))) {
                double value;
                status = m_interfaceListener.OnGetCurrentValue(value);
                if (status != ER_OK) {
                    value = GetCurrentValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCurrentValue(value);
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_MaxValue.compare(propName))) {
                double value;
                status = m_interfaceListener.OnGetMaxValue(value);
                if (status != ER_OK) {
                    value = GetMaxValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxValue(value);
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_MinValue.compare(propName))) {
                double value;
                status = m_interfaceListener.OnGetMinValue(value);
                if (status != ER_OK) {
                    value = GetMinValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMinValue(value);
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_Precision.compare(propName))) {
                double precision;
                status = m_interfaceListener.OnGetPrecision(precision);
                if (status != ER_OK) {
                    precision = GetPrecision();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetPrecision(precision);
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = precision;
            } else if (!(s_prop_UpdateMinTime.compare(propName))) {
                uint16_t updateMinTime;
                status = m_interfaceListener.OnGetUpdateMinTime(updateMinTime);
                if (status != ER_OK) {
                    updateMinTime = GetUpdateMinTime();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetUpdateMinTime(updateMinTime);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = updateMinTime;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_ContaminantType.compare(propName))) {
                uint8_t type = GetContaminantType();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = type;
            } else if (!(s_prop_CurrentValue.compare(propName))) {
                double value = GetCurrentValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_MaxValue.compare(propName))) {
                double value = GetMaxValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_MinValue.compare(propName))) {
                double value = GetMinValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_Precision.compare(propName))) {
                double precision = GetPrecision();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = precision;
            } else if (!(s_prop_UpdateMinTime.compare(propName))) {
                uint16_t updateMinTime = GetUpdateMinTime();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = updateMinTime;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus CurrentAirQualityIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void CurrentAirQualityIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus CurrentAirQualityIntfControlleeImpl::SetContaminantType(const uint8_t type)
{
    if( type < (uint8_t)CONTAMINANT_TYPE_CH2O || 
        type > (uint8_t)CONTAMINANT_TYPE_VOC)
    {
        QCC_LogError(ER_FAIL, ("%s: ContaminantType is invalid Value. ", __func__));
        return ER_FAIL;
    }
    if (m_contaminantType != type) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = type;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ContaminantType.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_contaminantType = type;
    }

    return ER_OK;
}

QStatus CurrentAirQualityIntfControlleeImpl::SetCurrentValue(const double value)
{
    double maxVal = GetMaxValue();
    double minVal = GetMinValue();
    if((value > maxVal && maxVal != DEFAULT_MAX_VALUE) || value < minVal)
    {
        QCC_LogError(ER_FAIL, ("%s: CurrentValue is invalid Value. ", __func__));
        return ER_FAIL;
    }

    if (m_currentValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_currentValue = value;
    }

    return ER_OK;
}

QStatus CurrentAirQualityIntfControlleeImpl::SetMaxValue(const double value)
{
    double minVal = GetMinValue();
    if (value < minVal)
    {
        QCC_LogError(ER_FAIL, ("%s: MaxValue is invalid Value. ", __func__));
        return ER_FAIL;
    }
    if (m_maxValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_maxValue = value;
    }

    return ER_OK;
}

QStatus CurrentAirQualityIntfControlleeImpl::SetMinValue(const double value)
{
    double maxVal = GetMaxValue();
    if(value > maxVal)
    {
        QCC_LogError(ER_FAIL, ("%s: MinValue is invalid Value. ", __func__));
        return ER_FAIL;
    }
    if (m_minValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MinValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_minValue = value;
    }

    return ER_OK;
}
QStatus CurrentAirQualityIntfControlleeImpl::SetPrecision(const double precision)
{
    QStatus status = ER_OK;

    if (m_precision != precision) {
        m_precision = precision;
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = precision;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Precision.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return status;
}

QStatus CurrentAirQualityIntfControlleeImpl::SetUpdateMinTime(const uint16_t updateMinTime)
{
    QStatus status = ER_OK;

    if (m_updateMinTime != updateMinTime) {
        m_updateMinTime = updateMinTime;
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = updateMinTime;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_UpdateMinTime.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return status;
}

} //namespace services
} //namespace ajn