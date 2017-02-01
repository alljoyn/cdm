/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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

#include "CurrentHumidityListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus CurrentHumidityListener::OnGetCurrentValue(uint8_t& value)
{
    cout << "CurrentHumidityListener::OnGetCurrentValue() - CurrentValue : " << (int)value << endl;
    return ER_OK;
}

QStatus CurrentHumidityListener::OnGetMaxValue(uint8_t& value)
{
    cout << "CurrentHumidityListener::OnGetMaxValue() - value : " << (int)value << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* CurrentHumidityCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new CurrentHumidityCommands(sample, objectPath);
}

CurrentHumidityCommands::CurrentHumidityCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

CurrentHumidityCommands::~CurrentHumidityCommands()
{
}

void CurrentHumidityCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_HUMIDITY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<CurrentHumidityIntfControllee*>(cdmInterface);

        RegisterCommand(&CurrentHumidityCommands::OnCmdGetCurrentValue, "gcv", "get current value");
        RegisterCommand(&CurrentHumidityCommands::OnCmdSetCurrentValue, "scv", "set current value (use 'scv <value>'");
        RegisterCommand(&CurrentHumidityCommands::OnCmdGetMaxValue, "gmv", "get max value");
        RegisterCommand(&CurrentHumidityCommands::OnCmdSetMaxValue, "smv", "set max value (use 'smv <value>'");
    } else {
        PrintCommands();
    }
}

void CurrentHumidityCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t maxvalue = 90;
        uint8_t currValue = 30;

        m_intfControllee->SetMaxValue(maxvalue);
        m_intfControllee->SetCurrentValue(currValue);
    }
}

void CurrentHumidityCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentHumidityIntfControllee* intfControllee = static_cast<CurrentHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetCurrentValue() << endl;
}

void CurrentHumidityCommands::OnCmdSetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentHumidityIntfControllee* intfControllee = static_cast<CurrentHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t currentValue = atoi(cmd.c_str());
    intfControllee->SetCurrentValue(currentValue);
}

void CurrentHumidityCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    CurrentHumidityIntfControllee* intfControllee = static_cast<CurrentHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMaxValue() << endl;
}

void CurrentHumidityCommands::OnCmdSetMaxValue(Commands* commands, std::string& cmd)
{
    CurrentHumidityIntfControllee* intfControllee = static_cast<CurrentHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = atoi(cmd.c_str());
    intfControllee->SetMaxValue(value);
}