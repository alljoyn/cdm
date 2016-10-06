/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "FanSpeedLevelListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus FanSpeedLevelListener::OnSetFanSpeedLevel(const uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnSetFanSpeedLevel() - FanSpeedLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnGetFanSpeedLevel(uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnGetFanSpeedLevel() - FanSpeedLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnGetMaxFanSpeedLevel(uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnGetMaxFanSpeedLevel() - MaxFanSpeedLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnSetAutoMode(const uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnSetAutoMode() - AutoMode : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnGetAutoMode(uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnGetAutoMode() - AutoMode : " << (int)value << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* FanSpeedLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new FanSpeedLevelCommands(sample, objectPath);
}

FanSpeedLevelCommands::FanSpeedLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

FanSpeedLevelCommands::~FanSpeedLevelCommands()
{
}

void FanSpeedLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(FAN_SPEED_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<FanSpeedLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&FanSpeedLevelCommands::OnCmdGetFanSpeedLevel, "gfsl", "get fan speed level");
        RegisterCommand(&FanSpeedLevelCommands::OnCmdSetFanSpeedLevel, "sfsl", "set fan speed level (use 'sfsl <fan spped level>'");
        RegisterCommand(&FanSpeedLevelCommands::OnCmdGetMaxFanSpeedLevel, "gmfsl", "get max fan speed level");
        RegisterCommand(&FanSpeedLevelCommands::OnCmdSetMaxFanSpeedLevel, "smfsl", "set max fan speed level (use 'smfsl <max fan speed level>'");
        RegisterCommand(&FanSpeedLevelCommands::OnCmdGetAutoMode, "fslgam", "get auto mode");
        RegisterCommand(&FanSpeedLevelCommands::OnCmdSetAutoMode, "fslsam", "set auto mode (use 'fslsam <0/1>'");
    } else {
        PrintCommands();
    }
}

void FanSpeedLevelCommands::OnCmdGetFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfControllee* intfControllee = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetFanSpeedLevel() << endl;
}

void FanSpeedLevelCommands::OnCmdSetFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfControllee* intfControllee = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int fanSpeedLevel = strtol(cmd.c_str(), NULL, 10);
    if (fanSpeedLevel < 0 || fanSpeedLevel >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetFanSpeedLevel((uint8_t)fanSpeedLevel);
}

void FanSpeedLevelCommands::OnCmdGetMaxFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfControllee* intfControllee = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMaxFanSpeedLevel() << endl;
}

void FanSpeedLevelCommands::OnCmdSetMaxFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfControllee* intfControllee = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int maxFanSpeedLevel = strtol(cmd.c_str(), NULL, 10);
    if (maxFanSpeedLevel < 0 || maxFanSpeedLevel >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetMaxFanSpeedLevel((uint8_t)maxFanSpeedLevel);
}

void FanSpeedLevelCommands::OnCmdGetAutoMode(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfControllee* intfControllee = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetAutoMode() << endl;
}

void FanSpeedLevelCommands::OnCmdSetAutoMode(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfControllee* intfControllee = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int autoMode = strtol(cmd.c_str(), NULL, 10);
    if (autoMode == 0x00 || autoMode == 0x01 || autoMode == 0xFF) {
        intfControllee->SetAutoMode((uint8_t)autoMode);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}