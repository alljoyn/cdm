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
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControlleeListener.h>
#include <algorithm>

#include "TimeDisplayIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TimeDisplayIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new TimeDisplayIntfControlleeImpl(busAttachment, dynamic_cast<TimeDisplayIntfControlleeListener&>(listener), cdmBusObject);
}

TimeDisplayIntfControlleeImpl::TimeDisplayIntfControlleeImpl(BusAttachment& busAttachment, TimeDisplayIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TimeDisplayIntfControlleeImpl::~TimeDisplayIntfControlleeImpl()
{
}

QStatus TimeDisplayIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus TimeDisplayIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if(!s_prop_DisplayTimeFormat.compare(propName)) {
                uint8_t timeFormat;
                status = m_interfaceListener.OnGetDisplayTimeFormat(timeFormat);
                if(status != ER_OK) {
                    QCC_LogError(status, ("%s: failed to get max level prop", __func__));
                }
                else {
                    //update and emit
                    SetDisplayTimeFormat(timeFormat);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = timeFormat;
            } else if (!s_prop_SupportedDisplayTimeFormats.compare(propName)) {
                std::vector<uint8_t> supportedTimeFormats;
                status = m_interfaceListener.OnGetSupportedDisplayTimeFormats(supportedTimeFormats);

                uint8_t* vals = new uint8_t[supportedTimeFormats.size()];

                size_t i = 0;

                for(i = 0; i < supportedTimeFormats.size(); i++)
                    vals[i] = (uint8_t)supportedTimeFormats[i];

                val.Set("ay", supportedTimeFormats.size(), vals);
                val.Stabilize();
                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if(!s_prop_DisplayTimeFormat.compare(propName)) {
                uint8_t timeFormat = GetDisplayTimeFormat();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = timeFormat;
            } else if(!s_prop_SupportedDisplayTimeFormats.compare(propName)) {
                std::vector<uint8_t> supportedTimeFormats = GetSupportedDisplayTimeFormats();
                uint8_t* vals = new uint8_t[supportedTimeFormats.size()];

                size_t i = 0;

                for(i = 0; i < supportedTimeFormats.size(); i++)
                    vals[i] = (uint8_t)supportedTimeFormats[i];

                val.Set("ay", supportedTimeFormats.size(), vals);
                val.Stabilize();
                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus TimeDisplayIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;
    if(!s_prop_DisplayTimeFormat.compare(propName)) {
        if(val.typeId != ALLJOYN_BYTE){
            status = ER_BUS_BAD_VALUE_TYPE;
            return status;
        } else {
            std::vector<uint8_t>::iterator it;
            uint8_t inputValue = val.v_byte;
            it = std::find(m_supportedDisplayTimeFormats.begin(), m_supportedDisplayTimeFormats.end(), inputValue);
            if(it == m_supportedDisplayTimeFormats.end()) {
                status = ER_INVALID_DATA;
                QCC_LogError(status, ("%s: property value not set ", __func__));
                return status;
            }
            status = m_interfaceListener.OnSetDisplayTimeFormat(val.v_byte);
            if(status != ER_OK) {
                status = ER_INVALID_DATA;
                QCC_LogError(status, ("%s: property value not set ", __func__));
            } else {
                status = SetDisplayTimeFormat(val.v_byte);
            }
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }
    return status;

}

void TimeDisplayIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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


QStatus TimeDisplayIntfControlleeImpl::SetDisplayTimeFormat(const uint8_t timeFormat)
{
    std::vector<uint8_t>::iterator it;
    it = std::find(m_supportedDisplayTimeFormats.begin(), m_supportedDisplayTimeFormats.end(), timeFormat);
    if(it == m_supportedDisplayTimeFormats.end()) {
        return ER_INVALID_DATA;
    }

    if(timeFormat != m_timeFormat)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_BYTE;
        arg.v_byte = timeFormat;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_DisplayTimeFormat.c_str(), arg, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_timeFormat = timeFormat;
    }
    return ER_OK;
}

QStatus TimeDisplayIntfControlleeImpl::SetSupportedDisplayTimeFormats(const std::vector<uint8_t>& supportedTimeFormats)
{

    MsgArg arg;
    uint8_t* vals = new uint8_t[supportedTimeFormats.size()];

    size_t i = 0;

    for(i = 0; i < supportedTimeFormats.size(); i++)
        vals[i] = (uint8_t)supportedTimeFormats[i];
    arg.Set("ay", supportedTimeFormats.size(), vals);
    arg.Stabilize();

    if(m_supportedDisplayTimeFormats.size() > 0)
        m_supportedDisplayTimeFormats.clear();

    for(i = 0; i < supportedTimeFormats.size(); i ++)
        m_supportedDisplayTimeFormats.push_back(supportedTimeFormats[i]);

    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedDisplayTimeFormats.c_str(), arg, SESSION_ID_ALL_HOSTED ,ALLJOYN_FLAG_GLOBAL_BROADCAST);
    delete[] vals;
    return ER_OK;
}


} //namespace services
} //namespace ajn