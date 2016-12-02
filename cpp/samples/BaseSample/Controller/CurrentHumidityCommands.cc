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
#include "CurrentHumidityCommands.h"
#include "ControllerSample.h"

CurrentHumidityListener::CurrentHumidityListener()
{
}

CurrentHumidityListener::~CurrentHumidityListener()
{
}

void CurrentHumidityListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentValue: " << (int)value << endl;
}

void CurrentHumidityListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << (int)value << endl;
}

void CurrentHumidityListener::OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentValue: " << (int)value << endl;
}

void CurrentHumidityListener::OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << (int)value << endl;
}

CurrentHumidityCommands::CurrentHumidityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

CurrentHumidityCommands::~CurrentHumidityCommands()
{
}

void CurrentHumidityCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_HUMIDITY_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<CurrentHumidityIntfController*>(cdmInterface);
    }

    RegisterCommand(&CurrentHumidityCommands::OnCmdGetCurrentValue, "gcv", "Get CurrentValue");
    RegisterCommand(&CurrentHumidityCommands::OnCmdGetMaxValue, "gmv", "get MaxValue");

    PrintCommands();
}

void CurrentHumidityCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentHumidityIntfController* intfController = static_cast<CurrentHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentValue();
}

void CurrentHumidityCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    CurrentHumidityIntfController* intfController = static_cast<CurrentHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxValue();
}