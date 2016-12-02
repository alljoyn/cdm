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
#include "OffControlCommands.h"
#include "ControllerSample.h"

OffControlListener::OffControlListener()
{
}

OffControlListener::~OffControlListener()
{
}

void OffControlListener::OnSwitchOff(QStatus status, const qcc::String& objectPath, void* context,
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

OffControlCommands::OffControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

OffControlCommands::~OffControlCommands()
{
}

void OffControlCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(OFF_CONTROL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<OffControlIntfController*>(cdmInterface);
    }

    RegisterCommand(&OffControlCommands::OffCmdSwitchOff, "off", "Switch Off");

    PrintCommands();
}

void OffControlCommands::OffCmdSwitchOff(Commands* commands, std::string& cmd)
{
    OffControlIntfController* intfController = static_cast<OffControlCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->SwitchOff();
}
