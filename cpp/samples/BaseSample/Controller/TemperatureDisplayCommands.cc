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

#include "TemperatureDisplayCommands.h"
#include "ControllerSample.h"

TemperatureDisplayListener::TemperatureDisplayListener()
{
}

TemperatureDisplayListener::~TemperatureDisplayListener()
{
}

void TemperatureDisplayListener::GetDisplayTemperatureUnitPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t temperatureUnit, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayTemperatureUnit: " << (int)temperatureUnit << endl;
}
void TemperatureDisplayListener::SetDisplayTemperatureUnitPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
}
void TemperatureDisplayListener::GetSupportedDisplayTemperatureUnitsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& supportedDisplayTemperatureUnits, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# supported temperature units: " << endl;
    for (size_t i = 0; i < supportedDisplayTemperatureUnits.size(); ++i) {
        cout << (int)supportedDisplayTemperatureUnits[i] << endl;
    }
}
void TemperatureDisplayListener::DisplayTemperatureUnitPropertyChanged(const qcc::String& objectPath, const uint8_t temperatureUnit)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayTemperatureUnit: " << (int)temperatureUnit << endl;

}
void TemperatureDisplayListener::SupportedDisplayTemperatureUnitsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& supportedDisplayTemperatureUnits)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# supported temperature units: " << endl;
    for (size_t i = 0; i < supportedDisplayTemperatureUnits.size(); ++i) {
        cout << (int)supportedDisplayTemperatureUnits[i] << endl;
    }
}

TemperatureDisplayCommands::TemperatureDisplayCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

TemperatureDisplayCommands::~TemperatureDisplayCommands()
{

}

void TemperatureDisplayCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TEMPERATURE_DISPLAY_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<TemperatureDisplayIntfController*>(cdmInterface);
    }

    RegisterCommand(&TemperatureDisplayCommands::OnCmdGetDisplayTemperatureUnit, "gdtu", "get display temperature unit");
    RegisterCommand(&TemperatureDisplayCommands::OnCmdSetDisplayTemperatureUnit, "sdtu", "set display temperature unit (use 'sdtu <0-Celsius/1-Fahrenheit/2-Kelvin>')");
    RegisterCommand(&TemperatureDisplayCommands::OnCmdGetSupportedDisplayTemperatureUnits, "gsdtu", "get supported display temperature unit");
    PrintCommands();
}


void TemperatureDisplayCommands::OnCmdGetDisplayTemperatureUnit(Commands* commands, std::string& cmd)
{
    TemperatureDisplayIntfController* intfController = static_cast<TemperatureDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetDisplayTemperatureUnit();
}

void TemperatureDisplayCommands::OnCmdGetSupportedDisplayTemperatureUnits(Commands* commands, std::string& cmd)
{
    TemperatureDisplayIntfController* intfController = static_cast<TemperatureDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedDisplayTemperatureUnits();
}
void TemperatureDisplayCommands::OnCmdSetDisplayTemperatureUnit(Commands* commands, std::string& cmd)
{
    TemperatureDisplayIntfController* intfController = static_cast<TemperatureDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    int temperatureUnit = strtol(cmd.c_str(), NULL, 10);

    intfController->SetDisplayTemperatureUnit(temperatureUnit);
}