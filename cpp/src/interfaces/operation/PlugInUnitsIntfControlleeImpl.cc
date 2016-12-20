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

#include <algorithm>
#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControlleeListener.h>

#include "PlugInUnitsIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* PlugInUnitsIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new PlugInUnitsIntfControlleeImpl(busAttachment, dynamic_cast<PlugInUnitsIntfControlleeListener&>(listener), cdmBusObject);
}

PlugInUnitsIntfControlleeImpl::PlugInUnitsIntfControlleeImpl(BusAttachment& busAttachment, PlugInUnitsIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

PlugInUnitsIntfControlleeImpl::~PlugInUnitsIntfControlleeImpl()
{
}

QStatus PlugInUnitsIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    return status;
}

QStatus PlugInUnitsIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!s_prop_PlugInUnits.compare(propName))
            {
                PlugInUnitsInterface::PlugInUnits units;
                status = m_interfaceListener.OnGetPlugInUnits(units);
                if (status != ER_OK) {
                    units = GetPlugInUnits();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetPlugInUnits(units); // update the value in ChannelIntfControllee.
                }

                int numUnits = units.size();
                MsgArg *args = new MsgArg[numUnits];
                int i = 0;
                for(PlugInUnitsInterface::PlugInUnits::iterator itr = units.begin();
                    itr != units.end(); ++itr) {
                    status = args[i].Set("(oub)", itr->objectPath.c_str(), itr->deviceId, itr->pluggedIn);
                    args[i++].Stabilize();
                }
                status = val.Set("a(oub)", i, args);
                val.Stabilize();
                delete [] args;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!s_prop_PlugInUnits.compare(propName))
            {
                PlugInUnitsInterface::PlugInUnits units = GetPlugInUnits();
                int numUnits = units.size();
                MsgArg *args = new MsgArg[numUnits];
                int i = 0;
                for(PlugInUnitsInterface::PlugInUnits::iterator itr = units.begin();
                        itr != units.end(); ++itr) {
                    status = args[i].Set("(oub)", itr->objectPath.c_str(), itr->deviceId, itr->pluggedIn);
                    args[i++].Stabilize();
                }
                status = val.Set("a(oub)", i, args);
                val.Stabilize();
                delete [] args;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus PlugInUnitsIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    /*
     * TODO: implement SetProperty
     */

    return status;
}

void PlugInUnitsIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus PlugInUnitsIntfControlleeImpl::SetPlugInUnits(const PlugInUnits& units)
{
    QStatus status = ER_OK;
    bool listChanged = false;

    if(m_plugInUnits.size() != units.size())
    {
        listChanged = true;
    }
    else
    {
        for (size_t i = 0; i < units.size(); i++)
        {
            PlugInInfo info;
            //PlugInUnits::iterator it = std::find(m_plugInUnits.begin(), m_plugInUnits.end(), units[i]);
            PlugInUnits::iterator it = std::find(m_plugInUnits.begin(), m_plugInUnits.end(), info);

            if(it == m_plugInUnits.end())
            {
                listChanged = true;
                break;
            }
        }
    }

    if(listChanged)
    {
        m_plugInUnits.clear();
        for(size_t i =0; i < units.size(); i++)
            m_plugInUnits.push_back(units[i]);

        PlugInUnitsInterface::PlugInUnits units = GetPlugInUnits();
        MsgArg val;
        int numUnits = units.size();
        MsgArg *args = new MsgArg[numUnits];
        int i = 0;
        for (PlugInUnitsInterface::PlugInUnits::iterator itr = units.begin();
                itr != units.end(); ++itr) {
            status = args[i].Set("(oub)", itr->objectPath.c_str(), itr->deviceId, itr->pluggedIn);
            args[i++].Stabilize();
        }
        status = val.Set("a(oub)", i, args);
        val.Stabilize();
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(),s_prop_PlugInUnits.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        delete [] args;
    }


    return status;
}

} //namespace services
} //namespace ajn