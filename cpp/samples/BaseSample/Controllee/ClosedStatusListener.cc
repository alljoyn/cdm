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
#include "ClosedStatusListener.h"
#include "ControlleeSample.h"


using namespace std;


QStatus ClosedStatusListener::OnGetIsClosed(bool& isClosed)
{
    cout << "ClosedStatusListener::OnGetIsClosed()" << endl;
    return ER_OK;
}

ControlleeCommands* ClosedStatusCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new ClosedStatusCommands(sample, objectPath);
}

ClosedStatusCommands::ClosedStatusCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

ClosedStatusCommands::~ClosedStatusCommands()
{
}

void ClosedStatusCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CLOSED_STATUS_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<ClosedStatusIntfControllee*>(cdmInterface);

        RegisterCommand(&ClosedStatusCommands::OnCmdGetClosedStatus, "gic", "get is closed");
        RegisterCommand(&ClosedStatusCommands::OnCmdSetClosedStatus, "sic", "set is closed (use 'sic <0/1>'");
    } else {
        PrintCommands();
    }
}

void ClosedStatusCommands::OnCmdGetClosedStatus(Commands* commands, std::string& cmd)
{
    ClosedStatusIntfControllee* intfControllee = static_cast<ClosedStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsClosed() << endl;

}
void ClosedStatusCommands::OnCmdSetClosedStatus(Commands* commands, std::string& cmd)
{
    ClosedStatusIntfControllee* intfControllee = static_cast<ClosedStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isClosed = strtol(cmd.c_str(), NULL, 10);
    if(isClosed != 0 && isClosed != 1)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetIsClosed((bool)isClosed);

}