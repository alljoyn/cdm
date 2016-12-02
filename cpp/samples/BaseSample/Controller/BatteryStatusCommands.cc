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
#include "BatteryStatusCommands.h"
#include "ControllerSample.h"

BatteryStatusListener::BatteryStatusListener()
{
}

BatteryStatusListener::~BatteryStatusListener()
{
}

void BatteryStatusListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t currentValue, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "currentValue: " << static_cast<int>(currentValue) << endl;
}

void BatteryStatusListener::OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool isCharging, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "isCharging: " << isCharging << endl;
}

void BatteryStatusListener::OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t currentValue)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "currentValue: " << static_cast<int>(currentValue) << endl;
}

void BatteryStatusListener::OnIsChargingChanged(const qcc::String& objectPath, const bool isCharging)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "isCharging: " << isCharging << endl;
}

BatteryStatusCommands::BatteryStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

BatteryStatusCommands::~BatteryStatusCommands()
{
}

void BatteryStatusCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(BATTERY_STATUS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<BatteryStatusIntfController*>(cdmInterface);
    }

    RegisterCommand(&BatteryStatusCommands::OnCmdGetCurrentValue, "gcv", "get current value of battery status");
    RegisterCommand(&BatteryStatusCommands::OnCmdGetIsCharging, "gic", "get battery charging status");
    PrintCommands();
}

void BatteryStatusCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfController* intfController = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentValue();
}

void BatteryStatusCommands::OnCmdGetIsCharging(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfController* intfController = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsCharging();
}