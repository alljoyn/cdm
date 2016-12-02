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

#include "AirRecirculationModeListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus AirRecirculationModeListener::OnSetIsRecirculating(const bool& isRecirculating)
{
    cout << "AirRecirculationModeListener::OnSetIsRecirculating() - isRecirculating : " << isRecirculating << endl;
    return ER_OK;
}

QStatus AirRecirculationModeListener::OnGetIsRecirculating(bool& isRecirculating)
{
    cout << "AirRecirculationModeListener::OnGetIsRecirculating()" << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* AirRecirculationModeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new AirRecirculationModeCommands(sample, objectPath);
}

AirRecirculationModeCommands::AirRecirculationModeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

AirRecirculationModeCommands::~AirRecirculationModeCommands()
{
}

void AirRecirculationModeCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(AIR_RECIRCULATION_MODE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<AirRecirculationModeIntfControllee*>(cdmInterface);

        RegisterCommand(&AirRecirculationModeCommands::OnCmdGetIsRecirculating, "gir", "get is recirculating");
        RegisterCommand(&AirRecirculationModeCommands::OnCmdSetIsRecirculating, "sir", "set is recirculating (use 'sir <0/1>'");
    } else {
        PrintCommands();
    }
}

void AirRecirculationModeCommands::OnCmdGetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfControllee* intfControllee = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsRecirculating() << endl;
}

void AirRecirculationModeCommands::OnCmdSetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfControllee* intfControllee = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isRecirculating = strtol(cmd.c_str(), NULL, 10);
    if (isRecirculating == 0 || isRecirculating == 1) {
        intfControllee->SetIsRecirculating(isRecirculating);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}