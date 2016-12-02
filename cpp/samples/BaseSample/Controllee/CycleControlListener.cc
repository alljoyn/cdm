/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include <iostream>
#include "CycleControlListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus CycleControlListener::OnGetOperationalState(CycleControlInterface::CycleControlOperationalState& state)
{
    cout << "CycleControlListener::OnGetOperationalState()" << endl;
    return ER_OK;
}

QStatus CycleControlListener::OnExecuteCommand(CycleControlInterface::CycleControlOperationalCommand command, CycleControlInterface::CycleControlOperationalState& newState, ErrorCode& error)
{
    QStatus status = ER_OK;
    cout << "CycleControlListener::OnExecuteCommand. Command: " << (int)command << ". Command name: " << CycleControlInterface::OPERATIONAL_COMMAND_STRINGS[command] <<endl;
    error = NOT_ERROR;
    newState = CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE;
    return status;
}


ControlleeCommands* CycleControlCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new CycleControlCommands(sample, objectPath);
}

CycleControlCommands::CycleControlCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

CycleControlCommands::~CycleControlCommands()
{
}

void CycleControlCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CYCLE_CONTROL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<CycleControlIntfControllee*>(cdmInterface);

        RegisterCommand(&CycleControlCommands::OnCmdGetOperationalState, "gos", "get operational state");
        RegisterCommand(&CycleControlCommands::OnCmdSetOperationalState, "sos", "set operational state (use 'sos <operational state>')");

        RegisterCommand(&CycleControlCommands::OnCmdGetSupportedOperationalCommands, "gsos", "get supported operational commands");
        RegisterCommand(&CycleControlCommands::OnCmdGetSupportedOperationalStates, "gsoc", "get supported operational states");

    } else {
        PrintCommands();
    }
}

void CycleControlCommands::InitializeProperties()
{
    if (m_intfControllee) {

    	CycleControlInterface::CycleControlOperationalState state = CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE;
		CycleControlInterface::SupportedOperationalStates states = {
	        CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE,
	        CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING,
	        CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START,
	        CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START,
	        CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED,
	        CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE
	    };

	    CycleControlInterface::SupportedOperationalCommands commands = {
		    CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_START,
	        CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_STOP,
	        CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_PAUSE,
	        CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_RESUME
		};

        m_intfControllee->SetSupportedStates(states);
        m_intfControllee->SetSupportedCommands(commands);
        m_intfControllee->SetOperationalState(state);
    }
}




void CycleControlCommands::OnCmdGetOperationalState(Commands* commands, std::string& cmd)
{

    CycleControlIntfControllee* intfControllee = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetOperationalState() << endl;
}
void CycleControlCommands::OnCmdSetOperationalState(Commands* commands, std::string& cmd)
{
    CycleControlIntfControllee* intfControllee = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t operationalState = strtol(cmd.c_str(), NULL, 10);

    if( operationalState < CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE ||
    	operationalState > CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE)
    {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetOperationalState((CycleControlInterface::CycleControlOperationalState)operationalState);
}

void CycleControlCommands::OnCmdGetSupportedOperationalCommands(Commands* commands, std::string& cmd)
{
    CycleControlIntfControllee* intfControllee = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const CycleControlInterface::SupportedOperationalCommands& supportedCommands = intfControllee->GetSupportedCommands();

    for (size_t i = 0 ; i < supportedCommands.size(); i ++)
    	cout << (int)supportedCommands[i] << " ";
    cout << endl;
}
void CycleControlCommands::OnCmdGetSupportedOperationalStates(Commands* commands, std::string& cmd)
{
    CycleControlIntfControllee* intfControllee = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const CycleControlInterface::SupportedOperationalStates& supportedStates = intfControllee->GetSupportedStates();

    for (size_t i = 0 ; i < supportedStates.size(); i ++)
    	cout << (int)supportedStates[i] << " ";
    cout << endl;
}