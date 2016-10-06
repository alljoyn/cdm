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
#include <algorithm>
#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControlleeListener.h>


#include "CycleControlIntfControlleeImpl.h"
#include <alljoyn/cdm/CdmBusObject.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CycleControlIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new CycleControlIntfControlleeImpl(busAttachment, dynamic_cast<CycleControlIntfControlleeListener&>(listener), cdmBusObject);
}

CycleControlIntfControlleeImpl::CycleControlIntfControlleeImpl(BusAttachment& busAttachment, CycleControlIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_currentState(OPERATIONAL_STATE_READY_TO_START)
{
}

CycleControlIntfControlleeImpl::~CycleControlIntfControlleeImpl()
{
}

QStatus CycleControlIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_ExecuteCommand.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&CycleControlIntfControlleeImpl::OnExecuteCommand);

    m_methodHandlers.push_back(make_pair(member, methodHandler));

    return status;
}

QStatus CycleControlIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    cout << "OnGet property. propname = " << propName << endl;
    if (!(s_prop_Version.compare(propName)))
    {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    }
    else if(!s_prop_SupportedOperationalCommands.compare(propName))
    {
        SupportedOperationalCommands commands = GetSupportedCommands();
        uint8_t* vals = new uint8_t[commands.size()];
        size_t i = 0;

        for(i = 0; i < commands.size(); i++)
        {
            vals[i] = (uint8_t)commands[i];
        }
        val.Set("ay", commands.size(), vals);
        val.Stabilize();
        delete[] vals;
    }
    else if(!s_prop_SupportedOperationalStates.compare(propName))
    {
        SupportedOperationalStates states = GetSupportedStates();
        uint8_t* vals = new uint8_t[states.size()];
        size_t i = 0;

        for(i = 0; i < states.size(); i++)
        {
            vals[i] = (uint8_t)states[i];
        }
        val.Set("ay", states.size(), vals);
        val.Stabilize();
        delete[] vals;
    }
    else
    {
        if (s_retrievingActualPropertyValue)
        {
            if(!s_prop_OperationalState.compare(propName))
            {
                CycleControlOperationalState state;
                status = m_interfaceListener.OnGetOperationalState(state);
                if (status != ER_OK)
                {
                    state = GetOperationalState();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                }
                else
                {
                    SetOperationalState(state);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = (uint8_t)state;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
        else
        {
            if (!(s_prop_OperationalState.compare(propName)))
            {
                const CycleControlOperationalState state = GetOperationalState();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = (uint8_t)state;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }
    return status;
}

QStatus CycleControlIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void CycleControlIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

void CycleControlIntfControlleeImpl::OnExecuteCommand(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;
    msg->GetArgs(numArgs, args);
    ErrorCode  error = ErrorCode::NOT_ERROR;
    CycleControlOperationalState newState = OPERATIONAL_STATE_IDLE;

    if (numArgs == 1)
    {
        CycleControlOperationalCommand command = (CycleControlOperationalCommand)args[0].v_byte;

        cout << "command: " << (int)command << "; command string: " << OPERATIONAL_COMMAND_STRINGS[command] << endl;

        SupportedOperationalCommands::iterator it;
        it = std::find(m_supportedCommands.begin(),m_supportedCommands.end(),command);
        if(it == m_supportedCommands.end())
        {
            m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(ErrorCode::INVALID_VALUE).c_str(), CdmInterface::GetInterfaceErrorMessage(ErrorCode::INVALID_VALUE).c_str());
            return;
        }


        status = m_interfaceListener.OnExecuteCommand(command, newState, error);
        if (status!= ER_OK)
        {
            QCC_LogError(status,("%s: failed to execute command.", __func__));
            m_busObject.ReplyMethodCall(msg, status);
            return;
        }
        else //status was not set (status is ER_OK)
        {
            if(error != ErrorCode::NOT_ERROR)
            {
                m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(error).c_str(), CdmInterface::GetInterfaceErrorMessage(error).c_str());
            }
            else
            {
                m_busObject.ReplyMethodCall(msg, status);
            }
        }
    }
    else
    {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }

}

QStatus CycleControlIntfControlleeImpl::SetOperationalState(CycleControlOperationalState state)
{
    SupportedOperationalStates::iterator it;
    it = std::find(m_supportedStates.begin(),m_supportedStates.end(),state);
    if(it == m_supportedStates.end())
    {
        return ER_FAIL;
    }

    QStatus status = ER_OK;

    if (m_currentState != state)
    {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = (uint8_t)state;
        m_currentState = state;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_OperationalState.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }
    return status;
}

QStatus CycleControlIntfControlleeImpl::SetSupportedCommands(SupportedOperationalCommands commands)
{
    QStatus status = ER_OK;

    bool listChanged = false;
    if(m_supportedCommands.size() != commands.size())
    {
        listChanged = true;
    }
    else
    {
        for (size_t i = 0; i < commands.size(); i ++)
        {
            SupportedOperationalCommands::iterator it;
            it = std::find(m_supportedCommands.begin(), m_supportedCommands.end(), commands[i]);
            if(it == m_supportedCommands.end())
            {
                listChanged = true;
                break;
            }
        }
    }

    if(listChanged)
    {
        m_supportedCommands.clear();
        for(unsigned int i =0;i<commands.size();i++)
            m_supportedCommands.push_back(commands[i]);
        uint8_t* vals = new uint8_t[m_supportedCommands.size()];
        MsgArg val;
        size_t i = 0;

        for(i = 0; i < m_supportedCommands.size(); i++)
        {
            vals[i] = (uint8_t)m_supportedCommands[i];
        }
        val.Set("ay", m_supportedCommands.size(), vals);
        val.Stabilize();
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(),s_prop_SupportedOperationalCommands.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        delete[] vals;
    }
    return status;
}
QStatus CycleControlIntfControlleeImpl::SetSupportedStates(SupportedOperationalStates states)
{
    QStatus status = ER_OK;

    bool listChanged = false;
    if(m_supportedStates.size() != states.size())
    {
        listChanged  = true;
    }
    else
    {
        for (size_t i = 0; i < states.size(); i ++)
        {
            SupportedOperationalStates::iterator it;
            it = std::find(m_supportedStates.begin(), m_supportedStates.end(), states[i]);
            if(it == m_supportedStates.end())
            {
                listChanged = true;
                break;
            }
        }
    }

    if(listChanged)
    {
        m_supportedStates.clear();
        for(unsigned int i =0;i<states.size();i++)
            m_supportedStates.push_back(states[i]);
        uint8_t* vals = new uint8_t[m_supportedStates.size()];

        MsgArg val;
        size_t i = 0;

        for(i = 0; i < m_supportedStates.size(); i++)
        {
            vals[i] = (uint8_t)m_supportedStates[i];
        }
        val.Set("ay", m_supportedStates.size(), vals);
        val.Stabilize();
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(),s_prop_SupportedOperationalStates.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        delete[] vals;
    }
    return status;
}

} //namespace services
} //namespace ajn