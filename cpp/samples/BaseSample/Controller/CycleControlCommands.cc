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

#include "CycleControlCommands.h"
#include "ControllerSample.h"

CycleControlListener::CycleControlListener()
{
}

CycleControlListener::~CycleControlListener()
{
}


void CycleControlListener::OperationalStatePropertyChanged(const qcc::String& objectPath, const CycleControlInterface::CycleControlOperationalState& state)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# state: " <<(int)state <<"; state string: "<< CycleControlInterface::OPERATIONAL_STATE_STRINGS[state] << endl;
}


void CycleControlListener::GetOperationalStatePropertyCallback(QStatus status, const qcc::String& objectPath, const CycleControlInterface::CycleControlOperationalState& state, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# state: " <<(int)state <<"; state string: "<< CycleControlInterface::OPERATIONAL_STATE_STRINGS[state] << endl;
}


void CycleControlListener::GetSupportedStatesPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported states: " << endl;
    for (size_t i = 0 ; i < states.size() ; i++)
    {
        cout << "# state: " << (int)states[i] << "; state string: " << CycleControlInterface::OPERATIONAL_STATE_STRINGS[states[i]] << endl;
    }
}

void CycleControlListener::GetSupportedCommandsPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported commands: " << endl;
    for (size_t i = 0 ; i < commands.size() ; i++)
    {
        cout << "# command: " << (int)commands[i] << "; command string: " << CycleControlInterface::OPERATIONAL_COMMAND_STRINGS[commands[i]] << endl;
    }
}

void CycleControlListener::SupportedOperationalStatesProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported states: " << endl;
    for (size_t i = 0 ; i < states.size() ; i++)
    {
        cout << "# state: " << (int)states[i] << "state string: " << CycleControlInterface::OPERATIONAL_STATE_STRINGS[states[i]] << endl;
    }
}

void CycleControlListener::SupportedOperationalCommandsProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported commands: " << endl;
    for (size_t i = 0 ; i < commands.size() ; i++)
    {
        cout << "# command: " << (int)commands[i] << "command string: " << CycleControlInterface::OPERATIONAL_COMMAND_STRINGS[commands[i]] << endl;
    }

}
void CycleControlListener::OnExecuteCommandRespose(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    cout << "# CycleControlListener::OnExecuteCommandRespose()" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    if(status != ER_OK)
    {
        cout << "# error name: " << errorName << endl;
        cout << "# error message: " << errorMessage << endl;
    }
}

CycleControlCommands::CycleControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

CycleControlCommands::~CycleControlCommands()
{

}

void CycleControlCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CYCLE_CONTROL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<CycleControlIntfController*>(cdmInterface);
    }

    RegisterCommand(&CycleControlCommands::OnCmdGetOperationalState, "gos", "get operational state");
    RegisterCommand(&CycleControlCommands::OnCmdExecuteCommand, "exec", "execute command");
    RegisterCommand(&CycleControlCommands::OnCmdGetSupportedOperationalCommands, "gsop", "get supported operational commands");
    RegisterCommand(&CycleControlCommands::OnCmdGetSupportedOperationalStates, "gsos", "get supported operational states");
    PrintCommands();
}

void CycleControlCommands::OnCmdGetSupportedOperationalCommands(Commands* commands, std::string& cmd)
{
    CycleControlIntfController* intfController = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedOperationalCommands();
}

void CycleControlCommands::OnCmdGetSupportedOperationalStates(Commands* commands, std::string& cmd)
{
    CycleControlIntfController* intfController = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfController) {

        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedOperationalStates();
}

void CycleControlCommands::OnCmdGetOperationalState(Commands* commands, std::string& cmd)
{
    CycleControlIntfController* intfController = static_cast<CycleControlCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetOperationalState();
}

void CycleControlCommands::OnCmdExecuteCommand(Commands * commands, std::string& cmd)
{
    CycleControlIntfController* intfController = static_cast<CycleControlCommands*>(commands)->GetInterface();
    if(!intfController)
    {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << "Command string: " << cmd.c_str() << endl;
    int command = strtol(cmd.c_str(), NULL, 10);
    if ( command >=0 && command <=3 ) {
        intfController->ExecuteCommand((CycleControlInterface::CycleControlOperationalCommand)command);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}
