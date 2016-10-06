/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "MoistureOutputLevelListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus MoistureOutputLevelListener::OnSetMoistureOutputLevel(const uint8_t& value)
{
    cout << "MoistureOutputLevelListener::OnSetMoistureOutputLevel() - MoistureOutputLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus MoistureOutputLevelListener::OnGetMoistureOutputLevel(uint8_t& value)
{
    cout << "MoistureOutputLevelListener::OnGetMoistureOutputLevel()" << endl;
    return ER_OK;
}

QStatus MoistureOutputLevelListener::OnGetMaxMoistureOutputLevel(uint8_t& value)
{
    cout << "MoistureOutputLevelListener::OnGetMaxMoistureOutputLevel()" << endl;
    return ER_OK;
}

QStatus MoistureOutputLevelListener::OnSetAutoMode(const uint8_t& autoMode)
{
    cout << "MoistureOutputLevelListener::OnSetAutoMode() - AutoMode : " << (int)autoMode << endl;
    return ER_OK;
}

QStatus MoistureOutputLevelListener::OnGetAutoMode(uint8_t& autoMode)
{
    cout << "MoistureOutputLevelListener::OnGetAutoMode()" << endl;
    return ER_OK;
}

/////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* MoistureOutputLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new MoistureOutputLevelCommands(sample, objectPath);
}

MoistureOutputLevelCommands::MoistureOutputLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

MoistureOutputLevelCommands::~MoistureOutputLevelCommands()
{
}

void MoistureOutputLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(MOISTURE_OUTPUT_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<MoistureOutputLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&MoistureOutputLevelCommands::OnCmdGetMoistureOutputLevel, "gmol", "get moisture output level");
        RegisterCommand(&MoistureOutputLevelCommands::OnCmdSetMoistureOutputLevel, "smol", "set moisture output level (use 'smol <value>'");
        RegisterCommand(&MoistureOutputLevelCommands::OnCmdGetMaxMoistureOutputLevel, "gmmol", "get max moisture output level");
        RegisterCommand(&MoistureOutputLevelCommands::OnCmdSetMaxMoistureOutputLevel, "smmol", "set max moisture output level (use 'smmol <max>'");
        RegisterCommand(&MoistureOutputLevelCommands::OnCmdGetAutoMode, "gmolam", "get auto mode");
        RegisterCommand(&MoistureOutputLevelCommands::OnCmdSetAutoMode, "smolam", "set auto mode(use 'smolam <0/1>'");
    } else {
        PrintCommands();
    }
}

void MoistureOutputLevelCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t moistureOutputLevel = 0;
        uint8_t autoMode = 0;

        m_intfControllee->SetMoistureOutputLevel(moistureOutputLevel);
        m_intfControllee->SetAutoMode(autoMode);
    }
}

void MoistureOutputLevelCommands::OnCmdGetMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfControllee* intfControllee = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetMoistureOutputLevel() << endl;
}

void MoistureOutputLevelCommands::OnCmdSetMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfControllee* intfControllee = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t moistureOutputLevel = strtol(cmd.c_str(), NULL, 10);
    uint8_t maxMoistureOutputLevel = intfControllee->GetMaxMoistureOutputLevel();
    if (moistureOutputLevel >= 0 && moistureOutputLevel <= maxMoistureOutputLevel) {
        intfControllee->SetMoistureOutputLevel(moistureOutputLevel);
    } else {
        cout << "Input argument is wrong. (0 ~ " << (int)maxMoistureOutputLevel << ")" << endl;
        return;
    }
}

void MoistureOutputLevelCommands::OnCmdGetMaxMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfControllee* intfControllee = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetMaxMoistureOutputLevel() << endl;
}

void MoistureOutputLevelCommands::OnCmdSetMaxMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfControllee* intfControllee = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxMoistureOutputLevel = strtol(cmd.c_str(), NULL, 10);
    if (maxMoistureOutputLevel >= 0) {
        intfControllee->SetMaxMoistureOutputLevel(maxMoistureOutputLevel);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}

void MoistureOutputLevelCommands::OnCmdGetAutoMode(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfControllee* intfControllee = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t result = intfControllee->GetAutoMode();
    if (result == MoistureOutputLevelInterface::ON) {
        cout << "ON" << endl;
    } else if (result  == MoistureOutputLevelInterface::OFF) {
        cout << "OFF" << endl;
    } else if (result  == MoistureOutputLevelInterface::NOT_SUPPORTED) {
        cout << "NOT_SUPPORTED" << endl;
    } else {
        cout << "UNKNOWN_VALUE : " << (int)result << endl;
    }
}

void MoistureOutputLevelCommands::OnCmdSetAutoMode(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfControllee* intfControllee = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t autoMode = strtol(cmd.c_str(), NULL, 10);
    if (autoMode != MoistureOutputLevelInterface::OFF &&
        autoMode != MoistureOutputLevelInterface::ON &&
        autoMode != MoistureOutputLevelInterface::NOT_SUPPORTED) {
        cout << "Input argument is wrong." << endl;
    } else {
        intfControllee->SetAutoMode(autoMode);
    }
}