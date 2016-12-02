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

#include "RemoteControllabilityCommands.h"
#include "ControllerSample.h"

RemoteControllabilityListener::RemoteControllabilityListener()
{
}

RemoteControllabilityListener::~RemoteControllabilityListener()
{
}


void RemoteControllabilityListener::IsControllablePropertyChanged(const qcc::String& objectPath, const bool isControllable)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# isControllable: " << isControllable << endl;
}


void RemoteControllabilityListener::GetIsControllablePropertyCallback(QStatus status, const qcc::String& objectPath, const bool isControllable, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# isControllable: " << isControllable<< endl;
}


RemoteControllabilityCommands::RemoteControllabilityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

RemoteControllabilityCommands::~RemoteControllabilityCommands()
{

}

void RemoteControllabilityCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(REMOTE_CONTROLLABILITY_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<RemoteControllabilityIntfController*>(cdmInterface);
    }

    RegisterCommand(&RemoteControllabilityCommands::OnCmdGetIsControllable, "grc", "get isControllable");
    PrintCommands();
}


void RemoteControllabilityCommands::OnCmdGetIsControllable(Commands* commands, std::string& cmd)
{
    RemoteControllabilityIntfController* intfController = static_cast<RemoteControllabilityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsControllable();
}
