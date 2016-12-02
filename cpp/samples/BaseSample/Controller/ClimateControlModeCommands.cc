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
#include "ClimateControlModeCommands.h"
#include "ControllerSample.h"

ClimateControlModeListener::ClimateControlModeListener()
{
}

ClimateControlModeListener::~ClimateControlModeListener()
{
}

void ClimateControlModeListener::OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void ClimateControlModeListener::OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Mode: " << value << endl;
}

void ClimateControlModeListener::OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "SupportedModes: ";
    for( int i=0 ;  i < (int)value.size() ; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
}

void ClimateControlModeListener::OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "OperationalState: " << value << endl;
}

void ClimateControlModeListener::OnModeChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "Mode: " << value << endl;
}

void ClimateControlModeListener::OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;

    for( int i=0 ;  i < (int)value.size() ; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;

}

void ClimateControlModeListener::OnOperationalStateChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "OperationalState: " << value << endl;
}



ClimateControlModeCommands::ClimateControlModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

ClimateControlModeCommands::~ClimateControlModeCommands()
{
}

void ClimateControlModeCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CLIMATE_CONTROL_MODE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<ClimateControlModeIntfController*>(cdmInterface);
    }

    RegisterCommand(&ClimateControlModeCommands::OnCmdGetMode, "getmode", "Get Mode");
    RegisterCommand(&ClimateControlModeCommands::OnCmdSetMode, "setmode", "Set Mode");
    RegisterCommand(&ClimateControlModeCommands::OnCmdGetSupportedModes, "getsm", "Get SupportedModes");
    RegisterCommand(&ClimateControlModeCommands::OnCmdGetOperationalState, "getos", "Get OperationalState");

    PrintCommands();
}

void ClimateControlModeCommands::OnCmdGetMode(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfController* intfController = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMode();
}

void ClimateControlModeCommands::OnCmdSetMode(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfController* intfController = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode < 0 || mode > 6) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetMode(mode);
}

void ClimateControlModeCommands::OnCmdGetSupportedModes(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfController* intfController = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedModes();
}

void ClimateControlModeCommands::OnCmdGetOperationalState(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfController* intfController = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetOperationalState();
}


