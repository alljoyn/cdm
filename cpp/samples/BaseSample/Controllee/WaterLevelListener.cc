/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>

#include "WaterLevelListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus WaterLevelListener::OnGetCurrentLevel(uint8_t& currentLevel)
{
    QStatus status = ER_OK;
    cout << "# WaterLevelListener::OnGetCurrentLevel()" << endl;
    cout << "Current level: " << (int)currentLevel << endl;
    return status;
}

QStatus WaterLevelListener::OnGetMaxLevel(uint8_t& maxLevel)
{
    QStatus status = ER_OK;
    cout << "# WaterLevelListener::OnGetMaxLevel()" << endl;
    cout << "Max level: " << (int)maxLevel << endl;
    return status;
}

QStatus WaterLevelListener::OnGetSupplySource(WaterLevelInterface::WaterLevelSupplySource& supplySource)
{
    QStatus status = ER_OK;
    cout << "# WaterLevelListener::OnGetSupplySource()" << endl;
    cout << "Supply Source: " << (int)supplySource << endl;
    return status;
}

ControlleeCommands* WaterLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new WaterLevelCommands(sample, objectPath);
}

WaterLevelCommands::WaterLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

WaterLevelCommands::~WaterLevelCommands()
{
}

void WaterLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(WATER_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<WaterLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&WaterLevelCommands::OnCmdGetMaxLevel, "gml", "get max level");
        RegisterCommand(&WaterLevelCommands::OnCmdSetMaxLevel, "sml", "set max level (use 'sml <max level>')");

        RegisterCommand(&WaterLevelCommands::OnCmdGetCurrentLevel, "gcl", "get current level");
        RegisterCommand(&WaterLevelCommands::OnCmdSetCurrentLevel, "scl", "set current level (use 'stl <target level>')");

        RegisterCommand(&WaterLevelCommands::OnCmdGetSupplySource, "gss", "get supply source");
        RegisterCommand(&WaterLevelCommands::OnCmdSetSupplySource, "sss", "set supply source (use 'sss <supply source>')");
    } else {
        PrintCommands();
    }
}

void WaterLevelCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t maxLevel = 6;
        uint8_t currentLevel = 1;
        WaterLevelInterface::WaterLevelSupplySource supplySource = WaterLevelInterface::WaterLevelSupplySource::SUPPLY_SOURCE_PIPE;
        
        m_intfControllee->SetCurrentLevel(currentLevel);
        m_intfControllee->SetMaxLevel(maxLevel);
        m_intfControllee->SetSupplySource(supplySource);
    }
}

void WaterLevelCommands::OnCmdGetCurrentLevel(Commands* commands, std::string& cmd)
{
    cout << "WaterLevelCommands::OnCmdGetCurrentLevel" << endl;
    WaterLevelIntfControllee* intfControllee = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetCurrentLevel() << endl;

}
void WaterLevelCommands::OnCmdSetCurrentLevel(Commands* commands, std::string& cmd)
{
    cout << "WaterLevelCommands::OnCmdSetCurrentLevel" << endl;
    WaterLevelIntfControllee* intfControllee = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t currnetLevel = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetCurrentLevel(currnetLevel);
}

void WaterLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    cout << "WaterLevelCommands::OnCmdGetMaxLevel" << endl;
    WaterLevelIntfControllee* intfControllee = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetMaxLevel() << endl;
}
void WaterLevelCommands::OnCmdSetMaxLevel(Commands* commands, std::string& cmd)
{
    cout << "WaterLevelCommands::OnCmdSetMaxLevel" << endl;
    WaterLevelIntfControllee* intfControllee = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxLevel = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetMaxLevel(maxLevel);
}

void WaterLevelCommands::OnCmdGetSupplySource(Commands* commands, std::string& cmd)
{
    cout << "WaterLevelCommands::OnCmdGetSupplySource" << endl;
    WaterLevelIntfControllee* intfControllee = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetSupplySource() << endl;

}
void WaterLevelCommands::OnCmdSetSupplySource(Commands* commands, std::string& cmd)
{
    cout << "WaterLevelCommands::OnCmdSetSupplySource" << endl;
    WaterLevelIntfControllee* intfControllee = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t supplySource = strtol(cmd.c_str(), NULL, 10);
    if(supplySource != WaterLevelInterface::WaterLevelSupplySource::SUPPLY_SOURCE_PIPE &&
       supplySource != WaterLevelInterface::WaterLevelSupplySource::SUPPLY_SOURCE_TANK &&
       supplySource != WaterLevelInterface::WaterLevelSupplySource::SUPPLY_SOURCE_NOT_SUPPORTED)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetSupplySource((WaterLevelInterface::WaterLevelSupplySource)supplySource);
}