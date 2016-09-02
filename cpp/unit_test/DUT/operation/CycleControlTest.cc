/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#include "CdmTest.h"
#include <algorithm>
#include <iostream>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllerListener.h>

using namespace std;
class CycleControlListener : public CycleControlIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;


    CycleControlInterface::CycleControlOperationalState m_operationalState;
    CycleControlInterface::CycleControlOperationalState m_operationalStateSignal;

    CycleControlInterface::SupportedOperationalStates m_supportedOperationalStates;
    CycleControlInterface::SupportedOperationalStates m_supportedOperationalStatesSignal;

    CycleControlInterface::SupportedOperationalCommands m_supportedOperationalCommands;
    CycleControlInterface::SupportedOperationalCommands m_supportedOperationalCommandsSignal;

    CycleControlInterface::SupportedOperationalCommands m_unSupportedOperationalCommands;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    std::vector<uint8_t> m_selectableLevels;
    std::vector<uint8_t> m_selectableLevelsSignal;
    virtual void GetOperationalStatePropertyCallback(QStatus status, const qcc::String& objectPath, const CycleControlInterface::CycleControlOperationalState& currentState, void* context)
    {
        m_status = status;
        m_operationalState = currentState;
        m_event.SetEvent();

    }
    virtual void GetSupportedStatesPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states, void* context)
    {
        m_status = status;
        m_supportedOperationalStates = states;
        m_event.SetEvent();
    }
    virtual void GetSupportedCommandsPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands, void* context)
    {
        m_status = status;
        m_supportedOperationalCommands = commands;
        m_event.SetEvent();
    }
    virtual void OperationalStatePropertyChanged(const qcc::String& objectPath, const CycleControlInterface::CycleControlOperationalState& currentState)
    {
        m_operationalStateSignal = currentState;
        m_eventSignal.SetEvent();
    }
    virtual void SupportedOperationalStatesProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states)
    {
        m_supportedOperationalStatesSignal = states;
        m_eventSignal.SetEvent();
    }
    virtual void SupportedOperationalCommandsProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands)
    {
        m_supportedOperationalCommandsSignal = commands;
        m_eventSignal.SetEvent();
    }
    virtual void OnExecuteCommandRespose(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
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
        CycleControlInterface::CycleControlOperationalCommand command = CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_START;
        CycleControlInterface::SupportedOperationalCommands::iterator it;

        it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);
        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }

        command = CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_STOP;
        it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);
        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }

        command = CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_PAUSE;
        it = std::find(m_supportedOperationalCommands.begin(),m_supportedOperationalCommands.end(),command);
        if(it == m_supportedOperationalCommands.end())
        {
            m_unSupportedOperationalCommands.push_back(command);
        }
        command = CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_RESUME;
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

        CycleControlListener listener;
        CdmInterface* interface = m_controller->CreateInterface(CYCLE_CONTROL_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        CycleControlIntfController* controller = static_cast<CycleControlIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the OperationalState property.");
            status = controller->GetOperationalState();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedOperationalStates property.");
            status = controller->GetSupportedOperationalStates();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve SupportedCommands property.");
            status = controller->GetSupportedOperationalCommands();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        TEST_LOG_1("Call ExecuteCommand method with invalid param.");
        {
            TEST_LOG_2("Generate list of unsupported commands");
            listener.GenerateUsupportedCommandsList();
            TEST_LOG_2("If size of unsupported commands list > 0, call ExecuteCommand method with 1st item of unsupported command list.");
            if(listener.m_unSupportedOperationalCommands.size() > 0)
            {
                const CycleControlInterface::CycleControlOperationalCommand invalidCommand = listener.m_unSupportedOperationalCommands[0];
                status = controller->ExecuteCommand(invalidCommand);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);
                EXPECT_STREQ(listener.m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());
            }
        }

        TEST_LOG_1("Call ExecuteCommand method with valid param.");
        {
            TEST_LOG_2("If size of supported commands list > 0, call ExecuteCommand method with 1st item of supported command list.");
            if(listener.m_supportedOperationalCommands.size() > 0)
            {
                const CycleControlInterface::CycleControlOperationalCommand validCommand = listener.m_supportedOperationalCommands[0];
                status = controller->ExecuteCommand(validCommand);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
            }
        }
    }
}
