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
#include "RepeatModeCommands.h"
#include "ControllerSample.h"

RepeatModeListener::RepeatModeListener()
{
}

RepeatModeListener::~RepeatModeListener()
{
}

void RepeatModeListener::OnResponseGetRepeatMode(QStatus status, const qcc::String& objectPath, const bool repeatMode, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "repeatMode: " << repeatMode << endl;
}

void RepeatModeListener::OnResponseSetRepeatMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void RepeatModeListener::OnRepeatModeChanged(const qcc::String& objectPath, const bool value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "value: " << value << endl;
}



RepeatModeCommands::RepeatModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

RepeatModeCommands::~RepeatModeCommands()
{
}

void RepeatModeCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(REPEAT_MODE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<RepeatModeIntfController*>(cdmInterface);
    }

    RegisterCommand(&RepeatModeCommands::OnCmdGetRepeatMode, "grm", "get repeat mode");
    RegisterCommand(&RepeatModeCommands::OnCmdSetRepeatMode, "srm", "set repeat mode");
    PrintCommands();
}

void RepeatModeCommands::OnCmdGetRepeatMode(Commands* commands, std::string& cmd)
{
    RepeatModeIntfController* intfController = static_cast<RepeatModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetRepeatMode();
}

void RepeatModeCommands::OnCmdSetRepeatMode(Commands* commands, std::string& cmd)
{
    RepeatModeIntfController* intfController = static_cast<RepeatModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    bool repeatMode = atoi(cmd.c_str());

    intfController->SetRepeatMode(repeatMode);
}