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

#include "CurrentAirQualityListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus CurrentAirQualityListener::OnGetContaminantType(uint8_t& type)
{
    cout << __func__ << " - contaminant type : " << (int)type << endl;
    return ER_OK;
}

QStatus CurrentAirQualityListener::OnGetCurrentValue(double& value)
{
    cout << __func__ << " - current value : " << value << endl;
    return ER_OK;
}

QStatus CurrentAirQualityListener::OnGetMaxValue(double& value)
{

    cout << __func__ << " - max value : " << value << endl;
    return ER_OK;
}

QStatus CurrentAirQualityListener::OnGetMinValue(double& value)
{
    cout << __func__ << " - min value : " << value << endl;
    return ER_OK;
}

QStatus CurrentAirQualityListener::OnGetPrecision(double& precision)
{
    cout << __func__ << " - precision type : " << precision << endl;
    return ER_OK;
}

QStatus CurrentAirQualityListener::OnGetUpdateMinTime(uint16_t& updateMinTime)
{
    cout << __func__ << " - update min time : " << updateMinTime << endl;
    return ER_OK;
}

////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* CurrentAirQualityCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new CurrentAirQualityCommands(sample, objectPath);
}

CurrentAirQualityCommands::CurrentAirQualityCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

CurrentAirQualityCommands::~CurrentAirQualityCommands()
{
}

void CurrentAirQualityCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_AIR_QUALITY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<CurrentAirQualityIntfControllee*>(cdmInterface);

        RegisterCommand(&CurrentAirQualityCommands::OnCmdGetContaminantType, "gct", "get contaminant type");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdSetContaminantType, "sct", "set contaminant type");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdGetCurrentValue, "gcv", "get current air quality");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdSetCurrentValue, "scv", "set current air quality");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdGetMaxValue, "gmax", "get maximum air quality");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdSetMaxValue, "smax", "set maximum air quality");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdGetMinValue, "gmin", "get minimum air quality");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdSetMinValue, "smin", "set minimum air quality");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdGetPrecision, "gpc", "get precision");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdSetPrecision, "spc", "set precision (use 'cpsp <precision>'");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdGetUpdateMinTime, "gumt", "get update min time");
        RegisterCommand(&CurrentAirQualityCommands::OnCmdSetUpdateMinTime, "sumt", "set update min time (use 'cpsumt <update min time>'");
    } else {
        PrintCommands();
    }
}

void CurrentAirQualityCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t contaminatType = CurrentAirQualityInterface::CONTAMINANT_TYPE_CH2O;
        double maxValue = 30.0;
        double minValue = 10.0;
        double currentValue = 15.0;
        double precision = 10;
        uint16_t updateMinTime = 1;

        m_intfControllee->SetContaminantType(contaminatType);
        m_intfControllee->SetMaxValue(maxValue);
        m_intfControllee->SetMinValue(minValue);
        m_intfControllee->SetCurrentValue(currentValue);
        m_intfControllee->SetPrecision(precision);
        m_intfControllee->SetUpdateMinTime(updateMinTime);
    }
}

void CurrentAirQualityCommands::OnCmdGetContaminantType(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetContaminantType() << endl;
}

void CurrentAirQualityCommands::OnCmdSetContaminantType(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = (uint8_t)stoi(cmd.c_str());
    intfControllee->SetContaminantType(value);
}

void CurrentAirQualityCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetCurrentValue() << endl;
}

void CurrentAirQualityCommands::OnCmdSetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

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
    intfControllee->SetCurrentValue(value);
}

void CurrentAirQualityCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMaxValue() << endl;
}

void CurrentAirQualityCommands::OnCmdSetMaxValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = stod(cmd.c_str());
    intfControllee->SetMaxValue(value);
}

void CurrentAirQualityCommands::OnCmdGetMinValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMinValue() << endl;
}

void CurrentAirQualityCommands::OnCmdSetMinValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = stod(cmd.c_str());
    intfControllee->SetMinValue(value);
}

void CurrentAirQualityCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetPrecision() << endl;
}
void CurrentAirQualityCommands::OnCmdSetPrecision(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = stod(cmd.c_str());
    intfControllee->SetPrecision(value);
}

void CurrentAirQualityCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetUpdateMinTime() << endl;
}

void CurrentAirQualityCommands::OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfControllee* intfControllee = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint16_t value = stoi(cmd.c_str());
    intfControllee->SetUpdateMinTime(value);
}