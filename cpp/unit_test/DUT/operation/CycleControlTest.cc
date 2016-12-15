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

#include "CdmTest.h"
#include <algorithm>
#include <iostream>
#include <interfaces/controller/operation/CycleControlIntfController.h>
#include <interfaces/controller/operation/CycleControlIntfControllerListener.h>

using namespace std;
class CycleControlListener : public CycleControlIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;


    CycleControlInterface::OperationalState m_operationalState;
    CycleControlInterface::OperationalState m_operationalStateSignal;

    std::vector<CycleControlInterface::OperationalState> m_supportedOperationalStates;
    std::vector<CycleControlInterface::OperationalState> m_supportedOperationalStatesSignal;

    std::vector<CycleControlInterface::OperationalCommands> m_supportedOperationalCommands;
    std::vector<CycleControlInterface::OperationalCommands> m_supportedOperationalCommandsSignal;

    std::vector<CycleControlInterface::OperationalCommands> m_unSupportedOperationalCommands;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    std::vector<uint8_t> m_selectableLevels;
    std::vector<uint8_t> m_selectableLevelsSignal;

    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const CycleControlInterface::OperationalState currentState, void* context) override
    {
        m_status = status;
        m_operationalState = currentState;
        m_event.SetEvent();

    }


    virtual void OnResponseGetSupportedOperationalStates(QStatus status, const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalState>& states, void* context) override
    {
        m_status = status;
        m_supportedOperationalStates = states;
        m_event.SetEvent();
    }


    virtual void OnResponseGetSupportedOperationalCommands(QStatus status, const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalCommands>& commands, void* context) override
    {
        m_status = status;
        m_supportedOperationalCommands = commands;
        m_event.SetEvent();
    }


    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const CycleControlInterface::OperationalState currentState) override
    {
        m_operationalStateSignal = currentState;
        m_eventSignal.SetEvent();
    }


    virtual void OnSupportedOperationalStatesChanged(const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalState>& states) override
    {
        m_supportedOperationalStatesSignal = states;
        m_eventSignal.SetEvent();
    }


    virtual void OnSupportedOperationalCommandsChanged(const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalCommands>& commands) override
    {
        m_supportedOperationalCommandsSignal = commands;
        m_eventSignal.SetEvent();
    }


    virtual void OnResponseExecuteOperationalCommand(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
    {
        m_status = status;
        if (status != ER_OK) {
            if (errorName) {
                m_errorName = errorName;
            }
            if (errorMessage) {
                m_errorMessage = errorMessage;
            }
        }
        m_event.SetEvent();
    }


    void GenerateUsupportedCommandsList()
    {
        CycleControlInterface::OperationalCommands command = CycleControlInterface::OPERATIONAL_COMMANDS_START;

        auto it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);
        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }

        command = CycleControlInterface::OPERATIONAL_COMMANDS_STOP;
        it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);
        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }

        command = CycleControlInterface::OPERATIONAL_COMMANDS_PAUSE;
        it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);
        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }
        command = CycleControlInterface::OPERATIONAL_COMMANDS_RESUME;
        it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);

        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }
    }
};



TEST_F(CDMTest, CDM_v1_CycleControl)
{
    WaitForControllee(CYCLE_CONTROL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<CycleControlListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.CycleControl", m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<CycleControlIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the OperationalState property.");
            status = controller->GetOperationalState();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedOperationalStates property.");
            status = controller->GetSupportedOperationalStates();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve SupportedCommands property.");
            status = controller->GetSupportedOperationalCommands();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }

        TEST_LOG_1("Call ExecuteCommand method with invalid param.");
        {
            TEST_LOG_2("Generate list of unsupported commands");
            listener->GenerateUsupportedCommandsList();
            TEST_LOG_2("If size of unsupported commands list > 0, call ExecuteCommand method with 1st item of unsupported command list.");
            if(listener->m_unSupportedOperationalCommands.size() > 0)
            {
                const CycleControlInterface::OperationalCommands invalidCommand = listener->m_unSupportedOperationalCommands[0];
                status = controller->ExecuteOperationalCommand(invalidCommand);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_NE(listener->m_status, ER_OK);
                EXPECT_STREQ(listener->m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());
            }
        }

        TEST_LOG_1("Call ExecuteCommand method with valid param.");
        {
            TEST_LOG_2("If size of supported commands list > 0, call ExecuteCommand method with 1st item of supported command list.");
            if(listener->m_supportedOperationalCommands.size() > 0)
            {
                const CycleControlInterface::OperationalCommands validCommand = listener->m_supportedOperationalCommands[0];
                status = controller->ExecuteOperationalCommand(validCommand);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
            }
        }
    }
}