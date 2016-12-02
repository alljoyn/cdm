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

#include <iostream>
#include "TemperatureDisplayListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus TemperatureDisplayListener::OnGetDisplayTemperatureUnit(uint8_t& temperatureUnit)
{
    cout << " TemperatureDisplayListener::OnGetDisplayTemperatureUnit" << endl;
    return ER_OK;
}

QStatus TemperatureDisplayListener::OnSetDisplayTemperatureUnit(const uint8_t temperatureUnit)
{
    cout << " TemperatureDisplayListener::OnSetDisplayTemperatureUnit" << endl;
    return ER_OK;
}

QStatus TemperatureDisplayListener::OnGetSupportedDisplayTemperatureUnits(std::vector<uint8_t>& supportedDisplayTemperatureUnits)
{
    cout << " TemperatureDisplayListener::OnGetSupportedDisplayTemperatureUnits" << endl;
    return ER_OK;
}


ControlleeCommands* TemperatureDisplayCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new TemperatureDisplayCommands(sample, objectPath);
}

TemperatureDisplayCommands::TemperatureDisplayCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

TemperatureDisplayCommands::~TemperatureDisplayCommands()
{
}

void TemperatureDisplayCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TEMPERATURE_DISPLAY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<TemperatureDisplayIntfControllee*>(cdmInterface);

        RegisterCommand(&TemperatureDisplayCommands::OnCmdGetDisplayTemperatureUnit, "gdtu", "get display temperature unit");
        RegisterCommand(&TemperatureDisplayCommands::OnCmdSetDisplayTemperatureUnit, "sdtu", "set display temperature unit(use 'sdtu <0-Celsius/1-Fahrenheit/2-Kelvin>')");
        RegisterCommand(&TemperatureDisplayCommands::OnCmdGetSupportedDisplayTemperatureUnits, "gsdtu", "get supported display temperature units");
    } else {
        PrintCommands();
    }
}

void TemperatureDisplayCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t temperatureUnit = 0;
        std::vector<uint8_t> supportedTemperatureUnits;

        supportedTemperatureUnits.push_back(0);
        supportedTemperatureUnits.push_back(1);
        supportedTemperatureUnits.push_back(2);

        m_intfControllee->SetDisplayTemperatureUnit(temperatureUnit);
        m_intfControllee->SetSupportedDisplayTemperatureUnits(supportedTemperatureUnits);
    }
}

void TemperatureDisplayCommands::OnCmdGetDisplayTemperatureUnit(Commands* commands, std::string& cmd)
{
    cout << "TemperatureDisplayCommands::OnCmdGetDisplayTimeFormat" << endl;
    TemperatureDisplayIntfControllee* intfControllee = static_cast<TemperatureDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetDisplayTemperatureUnit() << endl;
}
void TemperatureDisplayCommands::OnCmdSetDisplayTemperatureUnit(Commands* commands, std::string& cmd)
{
    cout << "TemperatureDisplayCommands::OnCmdSetDisplayTemperatureUnit" << endl;
    TemperatureDisplayIntfControllee* intfControllee = static_cast<TemperatureDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t temperatureUnit = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetDisplayTemperatureUnit(temperatureUnit);
}

void TemperatureDisplayCommands::OnCmdGetSupportedDisplayTemperatureUnits(Commands* commands, std::string& cmd)
{
    cout << "TemperatureDisplayCommands::OnCmdGetSupportedDisplayTemperatureUnits" << endl;
    TemperatureDisplayIntfControllee* intfControllee = static_cast<TemperatureDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const std::vector<uint8_t> supportedTemperatureUnits = intfControllee->GetSupportedDisplayTemperatureUnits();

    for(size_t i = 0; i < supportedTemperatureUnits.size(); i++)
        cout << (int)supportedTemperatureUnits[i] << " ";
    cout << endl;
}