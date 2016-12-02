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

#include "SoilLevelCommands.h"
#include "ControllerSample.h"

SoilLevelListener::SoilLevelListener()
{
}

SoilLevelListener::~SoilLevelListener()
{
}


void SoilLevelListener::MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# maxLevel: " << (int)maxLevel << endl;
}


void SoilLevelListener::GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# maxLevel: " << (int)maxLevel << endl;
}

void SoilLevelListener::GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# targetLevel: " << (int)targetLevel << endl;
}

void SoilLevelListener::SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# objectPath: " << objectPath << endl;
}

void SoilLevelListener::GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# selectable levels: " << endl;
    for (size_t i = 0; i < selectableLevels.size(); ++i) {
        cout << (int)selectableLevels[i] << endl;
    }
}

void SoilLevelListener::TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# targetLevel: " << (int)targetLevel << endl;
}

void SoilLevelListener::SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    for (size_t i = 0; i < selectableLevels.size(); ++i) {
        cout << (int)selectableLevels[i] << endl;
    }
}



SoilLevelCommands::SoilLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

SoilLevelCommands::~SoilLevelCommands()
{

}

void SoilLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(SOIL_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<SoilLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&SoilLevelCommands::OnCmdGetMaxLevel, "gml", "get max soil level");
    RegisterCommand(&SoilLevelCommands::OnCmdGetTargetLevel, "gtl", "get target soil level");
    RegisterCommand(&SoilLevelCommands::OnCmdSetTargetLevel, "stl", "set target soil level");
    RegisterCommand(&SoilLevelCommands::OnCmdGetSelectableLevels, "gsl", "get selectable levels");
    PrintCommands();
}


void SoilLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    SoilLevelIntfController* intfController = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetMaxLevel();
}

void SoilLevelCommands::OnCmdGetSelectableLevels(Commands* commands, std::string& cmd)
{
    SoilLevelIntfController* intfController = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSelectableLevels();
}
void SoilLevelCommands::OnCmdGetTargetLevel(Commands* commands, std::string& cmd)
{
    SoilLevelIntfController* intfController = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetLevel();
}
void SoilLevelCommands::OnCmdSetTargetLevel(Commands* commands, std::string& cmd)
{
    SoilLevelIntfController* intfController = static_cast<SoilLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    int level = strtol(cmd.c_str(), NULL, 10);
    if (level < 0 || level >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }

    intfController->SetTargetLevel(level);
}
