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

#include "OnOffStatusListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus OnOffStatusListener::OnGetIsOn(bool& value)
{
    cout << "OnOffStatusListener::OnGetIsOn() - OnOff : " << value << endl;
    return ER_OK;
}

///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* OnOffStatusCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new OnOffStatusCommands(sample, objectPath);
}

OnOffStatusCommands::OnOffStatusCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

OnOffStatusCommands::~OnOffStatusCommands()
{
}

void OnOffStatusCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ON_OFF_STATUS_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<OnOffStatusIntfControllee*>(cdmInterface);

        RegisterCommand(&OnOffStatusCommands::OnCmdGetIsOnStatus, "gos", "get on/off status");
        RegisterCommand(&OnOffStatusCommands::OnCmdSetIsOnStatus, "sos", "set on/off status(use 'sos <0/1>'");

    } else {
        PrintCommands();
    }
}

void OnOffStatusCommands::OnCmdGetIsOnStatus(Commands* commands, std::string& cmd)
{
    OnOffStatusIntfControllee* intfControllee = static_cast<OnOffStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsOn() << endl;
}

void OnOffStatusCommands::OnCmdSetIsOnStatus(Commands* commands, std::string& cmd)
{
    OnOffStatusIntfControllee* intfControllee = static_cast<OnOffStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int status = strtol(cmd.c_str(), NULL, 10);
    if (status == 0 || status == 1) {
        intfControllee->SetIsOn(status);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}