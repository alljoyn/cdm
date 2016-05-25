/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureIntfControlleeListener.h>
#include <alljoyn/hae/HaeBusObject.h>
#include "TargetTemperatureIntfControlleeImpl.h"
#include <cmath>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {


HaeInterface* TargetTemperatureIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new TargetTemperatureIntfControlleeImpl(busAttachment, static_cast<TargetTemperatureIntfControlleeListener&>(listener), haeBusObject);
}


TargetTemperatureIntfControlleeImpl::TargetTemperatureIntfControlleeImpl(BusAttachment& busAttachment, TargetTemperatureIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_TargetValue(0),
    m_MinValue(0),
    m_MaxValue(100),
    m_StepValue(1),
    m_currentStrategy(ROUNDING_TO_NEAREST_VALUE)
{
}

TargetTemperatureIntfControlleeImpl::~TargetTemperatureIntfControlleeImpl()
{
}

QStatus TargetTemperatureIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();

    return status;
}

QStatus TargetTemperatureIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;


    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_TargetValue.compare(propName))) {
                double value;
                status = m_interfaceListener.OnGetTargetValue(value);
                if (status != ER_OK) {
                    value = GetTargetValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetTargetValue(value); // update TargetValue in TargetTemperatureIntfControllee.
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
                    SetMinValue(value); // update MinValue in TargetTemperatureIntfControllee.
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
                    SetMaxValue(value); // update MaxValue in TargetTemperatureIntfControllee.
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if (!(s_prop_StepValue.compare(propName))) {
                double value;
                status = m_interfaceListener.OnGetStepValue(value);
                if (status != ER_OK) {
                    value = GetStepValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetStepValue(value); // update StepValue in TargetTemperatureIntfControllee.
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_TargetValue.compare(propName))) {
                const double value = GetTargetValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if(!(s_prop_MinValue.compare(propName))) {
                const double value = GetMinValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if(!(s_prop_MaxValue.compare(propName))) {
                const double value = GetMaxValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else if(!(s_prop_StepValue.compare(propName))) {
                const double value = GetStepValue();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus TargetTemperatureIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_TargetValue.compare(propName))) {
        if (val.typeId != ALLJOYN_DOUBLE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        double value = adjustTargetValue(val.v_double);
        status = m_interfaceListener.OnSetTargetValue(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetTargetValue(value); // update the value in TargetTemperatureIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void TargetTemperatureIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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


QStatus TargetTemperatureIntfControlleeImpl::SetTargetValue(const double value)
{
    if (value < m_MinValue || value > m_MaxValue) {
        QCC_LogError(ER_FAIL, ("%s: TargetTemperature is out of range. ", __func__));
        return ER_FAIL;
    }

    if (m_StepValue != 0 && std::fmod(value - m_MinValue, m_StepValue) != 0.0) {
        QCC_LogError(ER_FAIL, ("%s: TargetTemperature doesn't match with the granularity of the current step. ", __func__));
        return ER_FAIL;
    }

    if (m_TargetValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_TargetValue = value;
    }

    return ER_OK;
}

QStatus TargetTemperatureIntfControlleeImpl::SetMinValue(const double value)
{
    if (m_MinValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MinValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_MinValue = value;
    }

    return ER_OK;
}

QStatus TargetTemperatureIntfControlleeImpl::SetMaxValue(const double value)
{
    if (m_MaxValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_MaxValue = value;
    }

    return ER_OK;
}

QStatus TargetTemperatureIntfControlleeImpl::SetStepValue(const double value)
{
    if (m_StepValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_StepValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_StepValue = value;
    }

    return ER_OK;
}

QStatus TargetTemperatureIntfControlleeImpl::SetStrategyOfAdjustingTargetValue(AdjustTargetValue strategy) {
    switch(strategy) {
    case ROUNDING_TO_NEAREST_VALUE:
    case ROUNDING_OFF:
    case ROUNDING_UP:
        return ER_OK;
    default:
        return ER_FAIL;
    }
}

double TargetTemperatureIntfControlleeImpl::adjustTargetValue(double value) {
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
