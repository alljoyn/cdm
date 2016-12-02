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

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "OnControlCommands.h"
#include "ControllerSample.h"

OnControlListener::OnControlListener()
{
}

OnControlListener::~OnControlListener()
{
}

void OnControlListener::OnResponseSwitchOn(QStatus status, const qcc::String& objectPath, void* context,
                                         const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (status != ER_OK) {
        cout << "error name : " << errorName << endl;
        cout << "error message : " << errorMessage << endl;
    }
}

OnControlCommands::OnControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

OnControlCommands::~OnControlCommands()
{
}

void OnControlCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ON_CONTROL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<OnControlIntfController*>(cdmInterface);
    }

    RegisterCommand(&OnControlCommands::OnCmdSwitchOn, "on", "Switch On");

    PrintCommands();
}

void OnControlCommands::OnCmdSwitchOn(Commands* commands, std::string& cmd)
{
    OnControlIntfController* intfController = static_cast<OnControlCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->SwitchOn();
}
