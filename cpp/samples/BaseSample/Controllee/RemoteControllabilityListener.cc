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
#include "RemoteControllabilityListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus RemoteControllabilityListener::OnGetIsControllable(bool& isControllable)
{
    cout << "RemoteControllabilityListener::OnGetIsControllable()" << endl;
    return ER_OK;
}

ControlleeCommands* RemoteControllabilityCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new RemoteControllabilityCommands(sample, objectPath);
}

RemoteControllabilityCommands::RemoteControllabilityCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

RemoteControllabilityCommands::~RemoteControllabilityCommands()
{
}

void RemoteControllabilityCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(REMOTE_CONTROLLABILITY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<RemoteControllabilityIntfControllee*>(cdmInterface);

        RegisterCommand(&RemoteControllabilityCommands::OnCmdGetIsControllable, "gic", "get is controllable");
        RegisterCommand(&RemoteControllabilityCommands::OnCmdSetIsControllable, "sic", "set is controllable (use 'sic <0/1>'");
    } else {
        PrintCommands();
    }
}

void RemoteControllabilityCommands::OnCmdGetIsControllable(Commands* commands, std::string& cmd)
{
    RemoteControllabilityIntfControllee* intfControllee = static_cast<RemoteControllabilityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsControllable() << endl;

}
void RemoteControllabilityCommands::OnCmdSetIsControllable(Commands* commands, std::string& cmd)
{
    RemoteControllabilityIntfControllee* intfControllee = static_cast<RemoteControllabilityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isControllable = strtol(cmd.c_str(), NULL, 10);
    if(isControllable != 0 && isControllable != 1)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetIsControllable((bool)isControllable);

}