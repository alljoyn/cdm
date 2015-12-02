#include "ControllerSample.h"
#include "ControllerCommands.h"

ControllerCommands::ControllerCommands(ControllerSample* sample)
: m_sample(sample)
{
    RegisterCommand(&ControllerCommands::OnCmdHelp, "-h", "print command  list");
    RegisterCommand(&ControllerCommands::OnCmdBack, "-b", "go to previous commands");
    RegisterCommand(&ControllerCommands::OnCmdQuit, "-q", "quit");
}

ControllerCommands::~ControllerCommands()
{
}

void ControllerCommands::PrintCommands()
{
    PrintCommandList();
}

void ControllerCommands::Execute(std::string& cmd)
{
    std::string remain;
    std::string command = GetCommandToken(cmd, remain);
    CommandFuncMap::iterator itr = m_Commands.find(command);
    if (itr != m_Commands.end()) {
        (*itr->second.func)(this, remain);
    }
}

void ControllerCommands::OnCmdHelp(Commands* commands, std::string& cmd)
{
    commands->PrintCommands();
}

void ControllerCommands::OnCmdBack(Commands* commands, std::string& cmd)
{
    ControllerSample* sample = static_cast<ControllerCommands*>(commands)->GetControllerSample();
    sample->PopCommands();
}

void ControllerCommands::OnCmdQuit(Commands* commands, std::string& cmd)
{
    ControllerSample* sample = static_cast<ControllerCommands*>(commands)->GetControllerSample();
    sample->Quit();
}
