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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "CurrentTemperatureListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus CurrentTemperatureListener::OnGetCurrentValue(double& value)
{
    cout << "CurrentTemperatureListener::OnGetCurrentValue() - CurrentValue : " << value << endl;
    return ER_OK;
}

QStatus CurrentTemperatureListener::OnGetPrecision(double& precision)
{
    cout << "CurrentTemperatureListener::OnGetPrecision() - precision : " << precision << endl;
    return ER_OK;
}

QStatus CurrentTemperatureListener::OnGetUpdateMinTime(uint16_t& updateMinTime)
{
    cout << "CurrentTemperatureListener::OnGetUpdateMinTime() - updateMinTime : " << updateMinTime << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* CurrentTemperatureCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new CurrentTemperatureCommands(sample, objectPath);
}

CurrentTemperatureCommands::CurrentTemperatureCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

CurrentTemperatureCommands::~CurrentTemperatureCommands()
{
}

void CurrentTemperatureCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_TEMPERATURE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<CurrentTemperatureIntfControllee*>(cdmInterface);

        RegisterCommand(&CurrentTemperatureCommands::OnCmdGetCurrentValue, "ctgcv", "get current value");
        RegisterCommand(&CurrentTemperatureCommands::OnCmdSetCurrentValue, "ctscv", "set current value (use 'ctscv <value>'");
        RegisterCommand(&CurrentTemperatureCommands::OnCmdGetPrecision, "ctgp", "get precision");
        RegisterCommand(&CurrentTemperatureCommands::OnCmdSetPrecision, "ctsp", "set precision (use 'ctsp <precision>'");
        RegisterCommand(&CurrentTemperatureCommands::OnCmdGetUpdateMinTime, "ctgumt", "get update min time");
        RegisterCommand(&CurrentTemperatureCommands::OnCmdSetUpdateMinTime, "ctsumt", "set update min time (use 'ctsumt <update min time>'");
    } else {
        PrintCommands();
    }
}

void CurrentTemperatureCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfControllee* intfControllee = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetCurrentValue() << endl;
}

void CurrentTemperatureCommands::OnCmdSetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfControllee* intfControllee = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double currentValue = strtod(cmd.c_str(), NULL);
    intfControllee->SetCurrentValue(currentValue);
}

void CurrentTemperatureCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfControllee* intfControllee = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetPrecision() << endl;
}

void CurrentTemperatureCommands::OnCmdSetPrecision(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfControllee* intfControllee = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double precision = strtod(cmd.c_str(), NULL);
    intfControllee->SetPrecision(precision);
}

void CurrentTemperatureCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfControllee* intfControllee = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetUpdateMinTime() << endl;
}

void CurrentTemperatureCommands::OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfControllee* intfControllee = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int updateMinTime = strtol(cmd.c_str(), NULL, 10);
    if (updateMinTime < 0 || updateMinTime >= 65536) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetUpdateMinTime((uint16_t)updateMinTime);
}