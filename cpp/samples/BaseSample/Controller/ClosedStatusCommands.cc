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

#include "ClosedStatusCommands.h"
#include "ControllerSample.h"

ClosedStatusListener::ClosedStatusListener()
{
}

ClosedStatusListener::~ClosedStatusListener()
{
}


void ClosedStatusListener::IsClosedPropertyChanged(const qcc::String& objectPath, const bool isClosed)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "isClosed: " << isClosed << endl;
}


void ClosedStatusListener::GetIsClosedPropertyCallback(QStatus status, const qcc::String& objectPath, const bool isClosed, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "isClosed: " << isClosed << endl;
}

ClosedStatusCommands::ClosedStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

ClosedStatusCommands::~ClosedStatusCommands()
{

}

void ClosedStatusCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CLOSED_STATUS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<ClosedStatusIntfController*>(cdmInterface);
    }

    RegisterCommand(&ClosedStatusCommands::OnCmdGetIsClosed, "gcs", "get isClosed");
    PrintCommands();
}


void ClosedStatusCommands::OnCmdGetIsClosed(Commands* commands, std::string& cmd)
{
    ClosedStatusIntfController* intfController = static_cast<ClosedStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsClosed();
}
