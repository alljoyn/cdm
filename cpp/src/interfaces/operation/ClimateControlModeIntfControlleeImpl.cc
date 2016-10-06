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
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "ClimateControlModeIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ClimateControlModeIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new ClimateControlModeIntfControlleeImpl(busAttachment, static_cast<ClimateControlModeIntfControlleeListener&>(listener), cdmBusObject);
}

ClimateControlModeIntfControlleeImpl::ClimateControlModeIntfControlleeImpl(BusAttachment& busAttachment, ClimateControlModeIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_Mode(0),
    m_OperationalState(0)
{

}

ClimateControlModeIntfControlleeImpl::~ClimateControlModeIntfControlleeImpl()
{
}

QStatus ClimateControlModeIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}


QStatus ClimateControlModeIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_Mode.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetMode(value);
                if (status != ER_OK) {
                    value = GetMode();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMode(value);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_SupportedModes.compare(propName))) {
                SupportedModes value;
                status = m_interfaceListener.OnGetSupportedModes(value);
                if (status != ER_OK) {
                    value = GetSupportedModes();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetSupportedModes(value);
                }

                MsgArg arg(ALLJOYN_ARRAY);
                size_t numElements = value.size();
                uint16_t* temp = new uint16_t[numElements];
                for (size_t i = 0; i < numElements; i++)
                {
                    temp[i] =  value[i];
                }
                arg.Set("aq", numElements, temp);

                val = arg;
                delete[] temp;
            } else if (!(s_prop_OperationalState.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetOperationalState(value);
                if (status != ER_OK) {
                    value = GetOperationalState();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetOperationalState(value);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_Mode.compare(propName))) {
                const uint16_t value = GetMode();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_SupportedModes.compare(propName))) {
                const SupportedModes& value = GetSupportedModes();

                MsgArg arg(ALLJOYN_ARRAY);
                size_t numElements = value.size();
                uint16_t* temp = new uint16_t[numElements];
                for (size_t i = 0; i < numElements; i++)
                {
                    temp[i] =  value[i];
                }
                arg.Set("aq", numElements, temp);

                val = arg;
                delete[] temp;
            } else if (!(s_prop_OperationalState.compare(propName))) {
                const uint16_t value = GetOperationalState();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus ClimateControlModeIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;
    size_t i = 0;

    if (!(s_prop_Mode.compare(propName))) {
        if (val.typeId != ALLJOYN_UINT16) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint16_t value = val.v_uint16;

        for (i = 0; i < m_SupportedModes.size(); i++)
        {
            if (m_SupportedModes[i] == value)
            {
                break;
            }
        }

        if (i != m_SupportedModes.size()) {
            status = m_interfaceListener.OnSetMode(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to set property value", __func__));
                status = ER_BUS_PROPERTY_VALUE_NOT_SET;
            } else {
                SetMode(value);
            }
        } else {
            status = ER_INVALID_DATA;
        }

    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void ClimateControlModeIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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


QStatus ClimateControlModeIntfControlleeImpl::SetMode(const uint16_t mode)
{
    size_t i = 0;

    for (i = 0; i < m_SupportedModes.size(); i++) {
        if (mode == m_SupportedModes[i]) {
            break;
        }
    }
    if (i == m_SupportedModes.size()) {
        QCC_LogError(ER_INVALID_DATA, ("%s: Mode is not exist in SupportedModes.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_Mode != mode) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = mode;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Mode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_Mode = mode;
    }

    return ER_OK;
}

QStatus ClimateControlModeIntfControlleeImpl::SetSupportedModes(const SupportedModes& modes)
{
    QStatus status = ER_OK;
    uint32_t i=0;
    bool diff = false;

    for (i = 0; i < modes.size(); i++) {
        if (modes[i] < MIN_CLIMATE_CONTROL_MODE || modes[i] > MAX_CLIMATE_CONTROL_MODE) {
            status = ER_INVALID_DATA;
            QCC_LogError(status, ("%s: Unknown Mode is included.", __func__));
            return status;
        }
    }

    if (m_SupportedModes.size() != modes.size()) {
        diff = true;
    } else {
        for (i = 0; i < m_SupportedModes.size(); i++) {
            if (m_SupportedModes[i] != modes[i]) {
                diff = true;
                break;
            }
        }
    }

    if (diff) {
        MsgArg arg(ALLJOYN_ARRAY);
        size_t numElements = modes.size();
        uint16_t* temp = new uint16_t[numElements];
        for (size_t i = 0; i < numElements; i++) {
            temp[i] =  modes[i];
        }
        arg.Set("aq", numElements, temp);

        if (status != ER_OK) {
            QCC_LogError(status, ("%s: could not set Elements.", __func__));
        }

        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedModes.c_str(), arg, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_SupportedModes = modes;
        delete[] temp;
    }

    return ER_OK;
}

QStatus ClimateControlModeIntfControlleeImpl::SetOperationalState(const uint16_t state)
{
    if (state < MIN_CLIMATE_CONTROL_OPERATIONAL_STATE || state > MAX_CLIMATE_CONTROL_OPERATIONAL_STATE) {
        QCC_LogError(ER_INVALID_DATA, ("%s: Unknown OperationalState.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_OperationalState != state) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = state;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_OperationalState.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_OperationalState = state;
    }

    return ER_OK;
}

} //namespace services
} //namespace ajn