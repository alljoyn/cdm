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

#include "AirRecirculationModeCommands.h"
#include "ControllerSample.h"

AirRecirculationModeListener::AirRecirculationModeListener()
{
}

AirRecirculationModeListener::~AirRecirculationModeListener()
{
}

void AirRecirculationModeListener::OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void AirRecirculationModeListener::OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "isRecirculating: " << isRecirculating << endl;
}

void AirRecirculationModeListener::OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "isRecirculating: " << isRecirculating << endl;
}

AirRecirculationModeCommands::AirRecirculationModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

AirRecirculationModeCommands::~AirRecirculationModeCommands()
{

}

void AirRecirculationModeCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(AIR_RECIRCULATION_MODE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<AirRecirculationModeIntfController*>(cdmInterface);
    }

    RegisterCommand(&AirRecirculationModeCommands::OnCmdGetIsRecirculating, "gir", "get is recirculating");
    RegisterCommand(&AirRecirculationModeCommands::OnCmdSetIsRecirculating, "sir", "set is recirculating (use 'sir <0/1>'");
    PrintCommands();
}

void AirRecirculationModeCommands::OnCmdGetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfController* intfController = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsRecirculating();
}

void AirRecirculationModeCommands::OnCmdSetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfController* intfController = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isRecirculating = strtol(cmd.c_str(), NULL, 10);
    if (isRecirculating == 0 || isRecirculating == 1) {
        intfController->SetIsRecirculating(isRecirculating);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}