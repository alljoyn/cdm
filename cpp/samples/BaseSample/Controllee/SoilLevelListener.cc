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
#include "SoilLevelListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus SoilLevelListener::OnGetMaxLevel(uint8_t& maxLevel)
{
    cout << " SoilLevelListener::OnGetMaxLevel" << endl;
    return ER_OK;
}

QStatus SoilLevelListener::OnSetMaxLevel(const uint8_t& maxLevel)
{
    cout << "SoilLevelListener::OnSetMaxLevel " << endl;
    return ER_OK;
}

QStatus SoilLevelListener::OnGetTargetLevel(uint8_t& targetLevel)
{
    cout << "SoilLevelListener::OnGetTargetLevel " << endl;
    return ER_OK;
}

QStatus SoilLevelListener::OnSetTargetLevel(const uint8_t& targetLevel)
{
    cout << " SoilLevelListener::OnSetTargetLevel" << endl;
    return ER_OK;
}

QStatus SoilLevelListener::OnGetSelectableLevels(std::vector<uint8_t>& selectableLevels)
{
    cout << "SoilLevelListener::OnGetSelectableLevels " << endl;
    return ER_OK;
}

QStatus SoilLevelListener::OnSetSelectableLevels(const std::vector<uint8_t>& selectableLevels)
{
    cout << "SoilLevelListener::OnSetSelectableLevels " << endl;
    return ER_OK;
}

ControlleeCommands* SoilLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new SoilLevelCommands(sample, objectPath);
}

SoilLevelCommands::SoilLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

SoilLevelCommands::~SoilLevelCommands()
{
}

void SoilLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(SOIL_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<SoilLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&SoilLevelCommands::OnCmdGetMaxLevel, "gml", "get max level");
        RegisterCommand(&SoilLevelCommands::OnCmdSetMaxLevel, "sml", "set max level (use 'sml <max level>')");

        RegisterCommand(&SoilLevelCommands::OnCmdGetTargetLevel, "gtl", "get target level");
        RegisterCommand(&SoilLevelCommands::OnCmdSetTargetLevel, "stl", "set target level (use 'stl <target level>')");

        RegisterCommand(&SoilLevelCommands::OnCmdGetSelectableLevels, "gsell", "get selectable levels");
    } else {
        PrintCommands();
    }
}

void SoilLevelCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t maxLevel = 6;
        uint8_t targetLevel = 1;
        std::vector<uint8_t> selectableLevels;

        for (uint8_t i = 0 ; i <= maxLevel; i++ )
            selectableLevels.push_back(i);

        m_intfControllee->SetTargetLevel(targetLevel);
        m_intfControllee->SetMaxLevel(maxLevel);
        m_intfControllee->SetSelectableLevels(selectableLevels);
    }
}

void SoilLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    cout << "SoilLevelCommands::OnCmdGetMaxLevel" << endl;
    SoilLevelIntfControllee* intfControllee = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetMaxLevel() << endl;
}
void SoilLevelCommands::OnCmdSetMaxLevel(Commands* commands, std::string& cmd)
{
    cout << "SoilLevelCommands::OnCmdSetMaxLevel" << endl;
    SoilLevelIntfControllee* intfControllee = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxLevel = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetMaxLevel(maxLevel);
}

void SoilLevelCommands::OnCmdGetTargetLevel(Commands* commands, std::string& cmd)
{
    cout << "SoilLevelCommands::OnCmdGetTargetLevel" << endl;
    SoilLevelIntfControllee* intfControllee = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetTargetLevel() << endl;

}
void SoilLevelCommands::OnCmdSetTargetLevel(Commands* commands, std::string& cmd)
{
    cout << "SoilLevelCommands::OnCmdSetTargetLevel" << endl;
    SoilLevelIntfControllee* intfControllee = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t targetLevel = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetTargetLevel(targetLevel);
}

void SoilLevelCommands::OnCmdGetSelectableLevels(Commands* commands, std::string& cmd)
{
    cout << "SoilLevelCommands::OnCmdGetSelectableLevels" << endl;
    SoilLevelIntfControllee* intfControllee = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const std::vector<uint8_t> selectableLevels = intfControllee->GetSelectableLevels();

    for(size_t i = 0; i < selectableLevels.size(); i++)
        cout << (int)selectableLevels[i] << " ";
    cout << endl;
}