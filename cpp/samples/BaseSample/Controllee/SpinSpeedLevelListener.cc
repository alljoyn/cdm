/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include "SpinSpeedLevelListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus SpinSpeedLevelListener::OnGetMaxLevel(uint8_t& maxLevel)
{
    cout << " SpinSpeedLevelListener::OnGetMaxLevel" << endl;
    return ER_OK;
}

QStatus SpinSpeedLevelListener::OnSetMaxLevel(const uint8_t& maxLevel)
{
    cout << "SpinSpeedLevelListener::OnSetMaxLevel " << endl;
    return ER_OK;
}

QStatus SpinSpeedLevelListener::OnGetTargetLevel(uint8_t& targetLevel)
{
    cout << "SpinSpeedLevelListener::OnGetTargetLevel " << endl;
    return ER_OK;
}

QStatus SpinSpeedLevelListener::OnSetTargetLevel(const uint8_t& targetLevel)
{
    cout << " SpinSpeedLevelListener::OnSetTargetLevel" << endl;
    return ER_OK;
}

QStatus SpinSpeedLevelListener::OnGetSelectableLevels(std::vector<uint8_t>& selectableLevels)
{
    cout << "SpinSpeedLevelListener::OnGetSelectableLevels " << endl;
    return ER_OK;
}

QStatus SpinSpeedLevelListener::OnSetSelectableLevels(const std::vector<uint8_t>& selectableLevels)
{
    cout << "SpinSpeedLevelListener::OnSetSelectableLevels " << endl;
    return ER_OK;
}

ControlleeCommands* SpinSpeedLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new SpinSpeedLevelCommands(sample, objectPath);
}

SpinSpeedLevelCommands::SpinSpeedLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

SpinSpeedLevelCommands::~SpinSpeedLevelCommands()
{
}

void SpinSpeedLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(SPIN_SPEED_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<SpinSpeedLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&SpinSpeedLevelCommands::OnCmdGetMaxLevel, "gml", "get max level");
        RegisterCommand(&SpinSpeedLevelCommands::OnCmdSetMaxLevel, "sml", "set max level (use 'sml <max level>')");

        RegisterCommand(&SpinSpeedLevelCommands::OnCmdGetTargetLevel, "gtl", "get target level");
        RegisterCommand(&SpinSpeedLevelCommands::OnCmdSetTargetLevel, "stl", "set target level (use 'stl <target level>')");

        RegisterCommand(&SpinSpeedLevelCommands::OnCmdGetSelectableLevels, "gsell", "get selectable levels");
    } else {
        PrintCommands();
    }
}

void SpinSpeedLevelCommands::InitializeProperties()
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

void SpinSpeedLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    cout << "SpinSpeedLevelCommands::OnCmdGetMaxLevel" << endl;
    SpinSpeedLevelIntfControllee* intfControllee = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetMaxLevel() << endl;
}
void SpinSpeedLevelCommands::OnCmdSetMaxLevel(Commands* commands, std::string& cmd)
{
    cout << "SpinSpeedLevelCommands::OnCmdSetMaxLevel" << endl;
    SpinSpeedLevelIntfControllee* intfControllee = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxLevel = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetMaxLevel(maxLevel);
}

void SpinSpeedLevelCommands::OnCmdGetTargetLevel(Commands* commands, std::string& cmd)
{
    cout << "SpinSpeedLevelCommands::OnCmdGetTargetLevel" << endl;
    SpinSpeedLevelIntfControllee* intfControllee = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetTargetLevel() << endl;

}
void SpinSpeedLevelCommands::OnCmdSetTargetLevel(Commands* commands, std::string& cmd)
{
    cout << "SpinSpeedLevelCommands::OnCmdSetTargetLevel" << endl;
    SpinSpeedLevelIntfControllee* intfControllee = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t targetLevel = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetTargetLevel(targetLevel);
}

void SpinSpeedLevelCommands::OnCmdGetSelectableLevels(Commands* commands, std::string& cmd)
{
    cout << "SpinSpeedLevelCommands::OnCmdGetSelectableLevels" << endl;
    SpinSpeedLevelIntfControllee* intfControllee = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const std::vector<uint8_t> selectableLevels = intfControllee->GetSelectableLevels();

    for(size_t i = 0; i < selectableLevels.size(); i++)
        cout << (int)selectableLevels[i] << " ";
    cout << endl;
}