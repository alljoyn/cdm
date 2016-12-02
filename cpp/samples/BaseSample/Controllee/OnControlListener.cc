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
#include "OnControlListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus OnControlListener::OnSwitchOn(ErrorCode& errorCode)
{
    cout << "OnControlListener::OnSwitchOn() - ErrorCode : " << errorCode << endl;
    return ER_OK;
}
///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* OnControlCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new OnControlCommands(sample, objectPath);
}

OnControlCommands::OnControlCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

OnControlCommands::~OnControlCommands()
{
}

void OnControlCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ON_CONTROL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }
        m_intfControllee = static_cast<OnControlIntfControllee*>(cdmInterface);
    } else {
        PrintCommands();
    }
}