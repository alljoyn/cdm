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

#include "RapidModeCommands.h"
#include "ControllerSample.h"

RapidModeListener::RapidModeListener()
{
}

RapidModeListener::~RapidModeListener()
{
}


void RapidModeListener::RapidModePropertyChanged(const qcc::String& objectPath, const bool rapidMode)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# rapidMode: " << rapidMode << endl;
}


void RapidModeListener::OnGetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, const bool rapidMode, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# rapidMode: " << rapidMode << endl;
}

void RapidModeListener::OnSetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
}

RapidModeCommands::RapidModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

RapidModeCommands::~RapidModeCommands()
{

}

void RapidModeCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(RAPID_MODE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<RapidModeIntfController*>(cdmInterface);
    }
    RegisterCommand(&RapidModeCommands::OnCmdGetRapidMode, "grm", "get rapidMode");
    RegisterCommand(&RapidModeCommands::OnCmdSetRapidMode, "srm", "set rapidMode (use 'scs <0/1>'");
    PrintCommands();
}


void RapidModeCommands::OnCmdGetRapidMode(Commands* commands, std::string& cmd)
{
    RapidModeIntfController* intfController = static_cast<RapidModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetRapidMode();
}

void RapidModeCommands::OnCmdSetRapidMode(Commands* commands, std::string& cmd)
{
    RapidModeIntfController* intfController = static_cast<RapidModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int rapidMode = strtol(cmd.c_str(), NULL,10);
    cout << "set rapid mode: mode : " << rapidMode <<endl;
    if(rapidMode != 1 && rapidMode != 0) {
        cout << "invalid argument " << endl;
        return;
    }
    intfController->SetRapidMode(rapidMode);
}