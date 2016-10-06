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
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControlleeListener.h>
#include <algorithm>

#include "TemperatureDisplayIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TemperatureDisplayIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new TemperatureDisplayIntfControlleeImpl(busAttachment, dynamic_cast<TemperatureDisplayIntfControlleeListener&>(listener), cdmBusObject);
}

TemperatureDisplayIntfControlleeImpl::TemperatureDisplayIntfControlleeImpl(BusAttachment& busAttachment, TemperatureDisplayIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TemperatureDisplayIntfControlleeImpl::~TemperatureDisplayIntfControlleeImpl()
{
}

QStatus TemperatureDisplayIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus TemperatureDisplayIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if(!s_prop_DisplayTemperatureUnit.compare(propName)) {
                uint8_t temperatureUnit;
                status = m_interfaceListener.OnGetDisplayTemperatureUnit(temperatureUnit);
                if(status != ER_OK) {
                    QCC_LogError(status, ("%s: failed to get max level prop", __func__));
                }
                else {
                    //update and emit
                    SetDisplayTemperatureUnit(temperatureUnit);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = temperatureUnit;
            } else if (!s_prop_SupportedDisplayTemperatureUnits.compare(propName)) {
                std::vector<uint8_t> supportedTemperatureUnits;
                status = m_interfaceListener.OnGetSupportedDisplayTemperatureUnits(supportedTemperatureUnits);

                uint8_t* vals = new uint8_t[supportedTemperatureUnits.size()];

                size_t i = 0;

                for(i = 0; i < supportedTemperatureUnits.size(); i++)
                    vals[i] = (uint8_t)supportedTemperatureUnits[i];

                val.Set("ay", supportedTemperatureUnits.size(), vals);
                val.Stabilize();
                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if(!s_prop_DisplayTemperatureUnit.compare(propName)) {
                uint8_t temperatureUnit = GetDisplayTemperatureUnit();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = temperatureUnit;
            } else if(!s_prop_SupportedDisplayTemperatureUnits.compare(propName)) {
                std::vector<uint8_t> supportedTemperatureUnits = GetSupportedDisplayTemperatureUnits();
                uint8_t* vals = new uint8_t[supportedTemperatureUnits.size()];

                size_t i = 0;

                for(i = 0; i < supportedTemperatureUnits.size(); i++)
                    vals[i] = (uint8_t)supportedTemperatureUnits[i];

                val.Set("ay", supportedTemperatureUnits.size(), vals);
                val.Stabilize();
                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus TemperatureDisplayIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;
    if(!s_prop_DisplayTemperatureUnit.compare(propName)) {
        if(val.typeId != ALLJOYN_BYTE){
            status = ER_BUS_BAD_VALUE_TYPE;
            return status;
        } else {
            std::vector<uint8_t>::iterator it;
            uint8_t inputValue = val.v_byte;

            it = std::find(m_supportedTemperatureUnits.begin(), m_supportedTemperatureUnits.end(), inputValue);
            if(it == m_supportedTemperatureUnits.end()) {
                status = ER_INVALID_DATA;
                QCC_LogError(status, ("%s: property value not set ", __func__));
                return status;
            }
            status = m_interfaceListener.OnSetDisplayTemperatureUnit(val.v_byte);
            if(status != ER_OK) {
                status = ER_INVALID_DATA;
                QCC_LogError(status, ("%s: property value not set ", __func__));
            } else {
                status = SetDisplayTemperatureUnit(val.v_byte);
            }
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }
    return status;
}

void TemperatureDisplayIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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
        QCC_LogError(status, ("%s: could not found method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

QStatus TemperatureDisplayIntfControlleeImpl::SetDisplayTemperatureUnit(const uint8_t temperatureUnit)
{
    std::vector<uint8_t>::iterator it;
    it = std::find(m_supportedTemperatureUnits.begin(), m_supportedTemperatureUnits.end(), temperatureUnit);
    if(it == m_supportedTemperatureUnits.end()) {
        return ER_INVALID_DATA;
    }

    if(temperatureUnit != m_temperatureUnit)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_BYTE;
        arg.v_byte = temperatureUnit;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_DisplayTemperatureUnit.c_str(), arg, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_temperatureUnit = temperatureUnit;
    }
    return ER_OK;
}

QStatus TemperatureDisplayIntfControlleeImpl::SetSupportedDisplayTemperatureUnits(const std::vector<uint8_t>& supportedTemperatureUnits)
{
    MsgArg arg;
    uint8_t* vals = new uint8_t[supportedTemperatureUnits.size()];

    size_t i = 0;

    for(i = 0; i < supportedTemperatureUnits.size(); i++)
        vals[i] = (uint8_t)supportedTemperatureUnits[i];
    arg.Set("ay", supportedTemperatureUnits.size(), vals);
    arg.Stabilize();

    if(m_supportedTemperatureUnits.size() > 0)
        m_supportedTemperatureUnits.clear();

    for(i = 0; i < supportedTemperatureUnits.size(); i ++)
        m_supportedTemperatureUnits.push_back(supportedTemperatureUnits[i]);

    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedDisplayTemperatureUnits.c_str(), arg, SESSION_ID_ALL_HOSTED ,ALLJOYN_FLAG_GLOBAL_BROADCAST);
    delete[] vals;
    return ER_OK;

}

} //namespace services
} //namespace ajn