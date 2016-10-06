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
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControlleeListener.h>

#include "CurrentPowerIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CurrentPowerIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new CurrentPowerIntfControlleeImpl(busAttachment, dynamic_cast<CurrentPowerIntfControlleeListener&>(listener), cdmBusObject);
}

CurrentPowerIntfControlleeImpl::CurrentPowerIntfControlleeImpl(BusAttachment& busAttachment, CurrentPowerIntfControlleeListener& listener,
                                                               CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject), m_busAttachment(busAttachment), m_interfaceListener(listener), m_currentPower(0.0), m_precision(0.0), m_updateMinTime(0)
{
}

CurrentPowerIntfControlleeImpl::~CurrentPowerIntfControlleeImpl()
{
}

QStatus CurrentPowerIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus CurrentPowerIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_CurrentPower.compare(propName))) {
                double currentPower;
                status = m_interfaceListener.OnGetCurrentPower(currentPower);
                if (status != ER_OK) {
                    currentPower = GetCurrentPower();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCurrentPower(currentPower);  // update the value in CurrentPowerIntfControllee.
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = currentPower;
            } else if (!(s_prop_Precision.compare(propName))) {
                double precision;
                status = m_interfaceListener.OnGetPrecision(precision);
                if (status != ER_OK) {
                    precision = GetPrecision();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetPrecision(precision);  // update the value in CurrentPowerIntfControllee.
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
                    SetUpdateMinTime(updateMinTime);  // update the value in CurrentPowerIntfControllee.
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = updateMinTime;
            }
        } else {
            if (!(s_prop_CurrentPower.compare(propName))) {
                double currentPower = GetCurrentPower();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = currentPower;
            } else if (!(s_prop_Precision.compare(propName))) {
                double precision = GetPrecision();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = precision;
            } else if (!(s_prop_UpdateMinTime.compare(propName))) {
                uint16_t updateMinTime = GetUpdateMinTime();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = updateMinTime;
            }
        }
    }

    return status;
}

QStatus CurrentPowerIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_CurrentPower.compare(propName))) {
        if (val.typeId != ALLJOYN_DOUBLE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        double currentPower = val.v_double;
        status = m_interfaceListener.OnSetCurrentPower(currentPower);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetCurrentPower(currentPower); // update the value in CurrentPowerIntfControllee.
        }
    } else if (!(s_prop_Precision.compare(propName))) {
        if (val.typeId != ALLJOYN_DOUBLE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        double precision = val.v_double;
        status = m_interfaceListener.OnSetPrecision(precision);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetPrecision(precision); // update the value in CurrentPowerIntfControllee.
        }
    } else if (!(s_prop_UpdateMinTime.compare(propName))) {
        if (val.typeId != ALLJOYN_UINT16) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint16_t updateMinTime = val.v_uint16;
        status = m_interfaceListener.OnSetUpdateMinTime(updateMinTime);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetUpdateMinTime(updateMinTime); // update the value in CurrentPowerIntfControllee.
        }
    }

    return status;
}

void CurrentPowerIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus CurrentPowerIntfControlleeImpl::SetCurrentPower(const double currentPower)
{
    QStatus status = ER_OK;

    if (m_currentPower != currentPower) {
        m_currentPower = currentPower;
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = currentPower;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentPower.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return status;
}

QStatus CurrentPowerIntfControlleeImpl::SetPrecision(const double precision)
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

QStatus CurrentPowerIntfControlleeImpl::SetUpdateMinTime(const uint16_t updateMinTime)
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

}  //namespace services
}  //namespace ajn