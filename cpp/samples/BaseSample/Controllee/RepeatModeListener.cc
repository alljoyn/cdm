/*
 * RobotCleaningCycleListener.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: jiny1u
 */

#include "RepeatModeListener.h"
#include "ControlleeSample.h"

using namespace ajn;
using namespace services;

QStatus RepeatModeListener::OnSetRepeatMode(const bool repeatMode)
{
    std::cout << "RepeatModeListener::OnSetRepeatMode() - repeatMode : " << repeatMode << std::endl;
    return ER_OK;
}

QStatus RepeatModeListener::OnGetRepeatMode(bool& repeatMode)
{
    std::cout << "RobotCleaningCycleListener::OnGetRepeatMode()" << std::endl;
    return ER_OK;
}

///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* RepeatModeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new RepeatModeCommands(sample, objectPath);
}

RepeatModeCommands::RepeatModeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

RepeatModeCommands::~RepeatModeCommands()
{
}

void RepeatModeCommands::Init()
{
    if (!m_intfControllee) {
        HaeInterface* haeInterface = m_sample->CreateInterface(REPEAT_MODE_INTERFACE, m_objectPath, m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<RepeatModeIntfControllee*>(haeInterface);

        RegisterCommand(&RepeatModeCommands::OnCmdGetRepeatMode, "grm", "get repeat mode");
        RegisterCommand(&RepeatModeCommands::OnCmdSetRepeatMode, "srm", "set repeat mode(use 'srm <0/1>'");

    } else {
        PrintCommands();
    }
}

void RepeatModeCommands::OnCmdGetRepeatMode(Commands* commands, std::string& cmd)
{
    RepeatModeIntfControllee* intfControllee = static_cast<RepeatModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetRepeatMode() << endl;
}

void RepeatModeCommands::OnCmdSetRepeatMode(Commands* commands, std::string& cmd)
{
    RepeatModeIntfControllee* intfControllee = static_cast<RepeatModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode == 0 || mode == 1) {
        intfControllee->SetRepeatMode(mode);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}
