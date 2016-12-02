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
#include "CurrentPowerCommands.h"
#include "ControllerSample.h"

CurrentPowerListener::CurrentPowerListener()
{
}

CurrentPowerListener::~CurrentPowerListener()
{
}

void CurrentPowerListener::OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double currentPower, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentPower: " << currentPower << endl;
}

void CurrentPowerListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Precision: " << precision << endl;
}

void CurrentPowerListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "UpdateMinTime: " << updateMinTime << endl;
}

void CurrentPowerListener::OnCurrentPowerChanged(const qcc::String& objectPath, const double currentPower)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "currentPower: " << currentPower << endl;
}

void CurrentPowerListener::OnPrecisionChanged(const qcc::String& objectPath, const double precision)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "Precision: " << precision << endl;
}

void CurrentPowerListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "UpdateMinTime: " << updateMinTime << endl;
}

CurrentPowerCommands::CurrentPowerCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

CurrentPowerCommands::~CurrentPowerCommands()
{
}

void CurrentPowerCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_POWER_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<CurrentPowerIntfController*>(cdmInterface);
    }

    RegisterCommand(&CurrentPowerCommands::OnCmdGetCurrentPower, "grm", "get current power");
    RegisterCommand(&CurrentPowerCommands::OnCmdGetPrecision, "gp", "get precision");
    RegisterCommand(&CurrentPowerCommands::OnCmdGetUpdateMinTime, "gumt", "get update min time");
    PrintCommands();
}

void CurrentPowerCommands::OnCmdGetCurrentPower(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfController* intfController = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentPower();
}

void CurrentPowerCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfController* intfController = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetPrecision();
}

void CurrentPowerCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfController* intfController = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetUpdateMinTime();
}