#include "ControlleeSample.h"
#include "ControlleeCommands.h"

ControlleeCommands::ControlleeCommands(ControlleeSample* sample)
: m_sample(sample)
{
    RegisterCommand(&ControlleeCommands::OnCmdHelp, "-h", "print command  list");
    RegisterCommand(&ControlleeCommands::OnCmdBack, "-b", "go to previous commands");
    RegisterCommand(&ControlleeCommands::OnCmdQuit, "-q", "quit");
}

ControlleeCommands::~ControlleeCommands()
{
}

void ControlleeCommands::Init()
{
}

void ControlleeCommands::InitializeProperties()
{
    for (std::map<std::string, Commands*>::iterator itr = m_Children.begin(); itr != m_Children.end(); ++itr) {
        ControlleeCommands* commands = static_cast<ControlleeCommands*>(itr->second);
        commands->InitializeProperties();
    }
}

void ControlleeCommands::PrintCommands()
{
    PrintCommandList();
}

void ControlleeCommands::Execute(std::string& cmd)
{
    std::string remain;
    std::string command = GetCommandToken(cmd, remain);
    CommandFuncMap::iterator itr = m_Commands.find(command);
    if (itr != m_Commands.end()) {
        (*itr->second.func)(this, remain);
    }
}

void ControlleeCommands::OnCmdHelp(Commands* commands, std::string& cmd)
{
    commands->PrintCommands();
}

void ControlleeCommands::OnCmdBack(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();
    sample->PopCommands();
}

void ControlleeCommands::OnCmdQuit(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();
    sample->Quit();
}
