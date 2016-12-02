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

#include "PlugInUnitsListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus PlugInUnitsListener::OnGetPlugInUnits(PlugInUnitsInterface::PlugInUnits& plugInUnits)
{
    QStatus status = ER_OK;
    cout << "PlugInUnitsListener::OnGetPlugInUnits" << endl;
    for (size_t i = 0; i < plugInUnits.size(); i++)
    {
        cout << "object path: " << plugInUnits[i].objectPath
             << "device id: " << plugInUnits[i].deviceId
             << "plugged in: " << plugInUnits[i].pluggedIn << endl;
    }
    return status;
}

////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* PlugInUnitsCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new PlugInUnitsCommands(sample, objectPath);
}

PlugInUnitsCommands::PlugInUnitsCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

PlugInUnitsCommands::~PlugInUnitsCommands()
{
}

void PlugInUnitsCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(PLUG_IN_UNITS_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<PlugInUnitsIntfControllee*>(cdmInterface);

        RegisterCommand(&PlugInUnitsCommands::OnCmdGetPlugInUnits, "gct", "get plug in units");
    } else {
        PrintCommands();
    }
}

void PlugInUnitsCommands::InitializeProperties()
{
    if (m_intfControllee) {
        PlugInUnitsInterface::PlugInInfo info1, info2;
        info1.objectPath = "/Cdm/IntegratedControllee";
        info1.deviceId = 1;
        info1.pluggedIn = false;

        info2.objectPath = "/Cdm/IntegratedControllee";
        info2.deviceId = 2;
        info2.pluggedIn = true;

        PlugInUnitsInterface::PlugInUnits units;
        units.push_back(info1);
        units.push_back(info2);

        m_intfControllee->SetPlugInUnits(units);
    }
}

void PlugInUnitsCommands::OnCmdGetPlugInUnits(Commands* commands, std::string& cmd)
{
    PlugInUnitsIntfControllee* intfControllee = static_cast<PlugInUnitsCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    PlugInUnitsInterface::PlugInUnits units = intfControllee->GetPlugInUnits();
    for (size_t i = 0; i < units.size(); i++)
    {
        cout << "Unit " << i << endl;
        cout << "  object path: " << units[i].objectPath << endl;
        cout << "  device id: " << units[i].deviceId << endl;
        cout << "  plugged in: " << units[i].pluggedIn << endl;
    }
}