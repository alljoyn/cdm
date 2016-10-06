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

#include "TargetTemperatureListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus TargetTemperatureListener::OnSetTargetValue(const double value)
{
    cout << "TargetTemperatureListener::OnSetTargetValue() - TargetValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetTargetValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetTargetValue() - TargetValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetMinValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetMinValue() - MinValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetMaxValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetMaxValue() - MaxValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetStepValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetStepValue() - StepValue : " << value << endl;
    return ER_OK;
}

////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* TargetTemperatureCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new TargetTemperatureCommands(sample, objectPath);
}

TargetTemperatureCommands::TargetTemperatureCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

TargetTemperatureCommands::~TargetTemperatureCommands()
{
}

void TargetTemperatureCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TARGET_TEMPERATURE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<TargetTemperatureIntfControllee*>(cdmInterface);

        RegisterCommand(&TargetTemperatureCommands::OnCmdGetTargetValue, "gtv", "get target value");
        RegisterCommand(&TargetTemperatureCommands::OnCmdSetTargetValue, "stv", "set target value (use 'stv <value>'");
        RegisterCommand(&TargetTemperatureCommands::OnCmdGetMinValue, "gmn", "get min value");
        RegisterCommand(&TargetTemperatureCommands::OnCmdSetMinValue, "smn", "set min value (use 'smn <value>'");
        RegisterCommand(&TargetTemperatureCommands::OnCmdGetMaxValue, "gmx", "get max value");
        RegisterCommand(&TargetTemperatureCommands::OnCmdSetMaxValue, "smx", "set max value (use 'smx <value>'");
        RegisterCommand(&TargetTemperatureCommands::OnCmdGetStepValue, "gsv", "get step value");
        RegisterCommand(&TargetTemperatureCommands::OnCmdSetStepValue, "ssv", "set step value (use 'ssv <value>'");
    } else {
        PrintCommands();
    }
}

void TargetTemperatureCommands::InitializeProperties()
{
    if (m_intfControllee) {
        double maxvalue = 30;
        double minvalue = -30;
        double targetvalue = 0;
        double stepvalue = 5;

        m_intfControllee->SetMaxValue(maxvalue);
        m_intfControllee->SetMinValue(minvalue);
        m_intfControllee->SetTargetValue(targetvalue);
        m_intfControllee->SetStepValue(stepvalue);
        m_intfControllee->SetStrategyOfAdjustingTargetValue(TargetTemperatureIntfControllee::ROUNDING_TO_NEAREST_VALUE);
    }
}

void TargetTemperatureCommands::OnCmdGetTargetValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetTargetValue() << endl;
}

void TargetTemperatureCommands::OnCmdSetTargetValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double minValue = intfControllee->GetMinValue();
    double maxValue = intfControllee->GetMaxValue();
    double value = stod(cmd.c_str());
    if (value < minValue || value > maxValue) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetTargetValue(value);
}

void TargetTemperatureCommands::OnCmdGetMinValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMinValue() << endl;
}

void TargetTemperatureCommands::OnCmdSetMinValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = stod(cmd.c_str());
    intfControllee->SetMinValue(value);
}

void TargetTemperatureCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMaxValue() << endl;
}

void TargetTemperatureCommands::OnCmdSetMaxValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = stod(cmd.c_str());
    intfControllee->SetMaxValue(value);
}

void TargetTemperatureCommands::OnCmdGetStepValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetStepValue() << endl;
}

void TargetTemperatureCommands::OnCmdSetStepValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfControllee* intfControllee = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = stod(cmd.c_str());
    intfControllee->SetStepValue(value);
}