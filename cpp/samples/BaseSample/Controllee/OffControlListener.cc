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
#include "OffControlListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus OffControlListener::OnSwitchOff(ErrorCode& errorCode)
{
    cout << "OffControlListener::OnSwitchOff() - ErrorCode : " << errorCode << endl;
    return ER_OK;
}
///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* OffControlCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new OffControlCommands(sample, objectPath);
}

OffControlCommands::OffControlCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

OffControlCommands::~OffControlCommands()
{
}

void OffControlCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(OFF_CONTROL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }
        m_intfControllee = static_cast<OffControlIntfControllee*>(cdmInterface);
    } else {
        PrintCommands();
    }
}