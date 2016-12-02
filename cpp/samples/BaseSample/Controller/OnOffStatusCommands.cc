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
#include "OnOffStatusCommands.h"
#include "ControllerSample.h"

OnOffStatusListener::OnOffStatusListener()
{
}

OnOffStatusListener::~OnOffStatusListener()
{
}

void OnOffStatusListener::OnIsOnChanged(const qcc::String& objectPath, const bool value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "IsOn: " << value << endl;
}

void OnOffStatusListener::OnResponseGetIsOn(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "IsOn: " << value << endl;
}

OnOffStatusCommands::OnOffStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

OnOffStatusCommands::~OnOffStatusCommands()
{
}

void OnOffStatusCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ON_OFF_STATUS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<OnOffStatusIntfController*>(cdmInterface);
    }

    RegisterCommand(&OnOffStatusCommands::OnCmdOnOffStatus, "onoff", "Current IsOn Status");

    PrintCommands();
}

void OnOffStatusCommands::OnCmdOnOffStatus(Commands* commands, std::string& cmd)
{
    OnOffStatusIntfController* intfController = static_cast<OnOffStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsOn();
}
