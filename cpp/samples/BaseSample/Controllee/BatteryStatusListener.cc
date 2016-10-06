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

#include "BatteryStatusListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus BatteryStatusListener::OnGetCurrentValue(uint8_t& currentValue)
{
    cout << "BatteryStatusListener::OnGetCurrentValue() - currentValue : " << (int)currentValue << endl;
    return ER_OK;
}

QStatus BatteryStatusListener::OnGetIsCharging(bool& isCharging)
{
    cout << "BatteryStatusListener::OnGetIsCharging() - isCharging : " << isCharging << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* BatteryStatusCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new BatteryStatusCommands(sample, objectPath);
}

BatteryStatusCommands::BatteryStatusCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

BatteryStatusCommands::~BatteryStatusCommands()
{
}

void BatteryStatusCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(BATTERY_STATUS_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<BatteryStatusIntfControllee*>(cdmInterface);

        RegisterCommand(&BatteryStatusCommands::OnCmdGetCurrentValue, "bsgcv", "get current value");
        RegisterCommand(&BatteryStatusCommands::OnCmdSetCurrentValue, "bsscv", "set current value (use 'bsscv <value>'");
        RegisterCommand(&BatteryStatusCommands::OnCmdGetIsCharging, "bsgic", "get is charging");
        RegisterCommand(&BatteryStatusCommands::OnCmdSetIsCharging, "bssic", "set is charging (use 'bssic <0/1>'");
    } else {
        PrintCommands();
    }
}

void BatteryStatusCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfControllee* intfControllee = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetCurrentValue() << endl;
}

void BatteryStatusCommands::OnCmdSetCurrentValue(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfControllee* intfControllee = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int currentValue = strtol(cmd.c_str(), NULL, 10);
    if (currentValue < 0 || currentValue > 100) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetCurrentValue((uint8_t)currentValue);
}

void BatteryStatusCommands::OnCmdGetIsCharging(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfControllee* intfControllee = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsCharging() << endl;
}

void BatteryStatusCommands::OnCmdSetIsCharging(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfControllee* intfControllee = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isCharging = strtol(cmd.c_str(), NULL, 10);
    if (isCharging == 0 || isCharging == 1) {
        intfControllee->SetIsCharging(isCharging);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}