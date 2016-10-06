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

#include "EnergyUsageListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus EnergyUsageListener::OnGetCumulativeEnergy(double& cumulativeEnergy)
{
    cout << "EnergyUsageListener::OnGetCumulativeEnergy()" << endl;
    return ER_OK;
}

QStatus EnergyUsageListener::OnGetPrecision(double& precision)
{
    cout << "EnergyUsageListener::OnGetPrecision()" << endl;
    return ER_OK;
}

QStatus EnergyUsageListener::OnGetUpdateMinTime(uint16_t& updateMinTime)
{
    cout << "EnergyUsageListener::OnGetUpdateMinTime()" << endl;
    return ER_OK;
}

QStatus EnergyUsageListener::OnResetCumulativeEnergy(ErrorCode& errorCode)
{
    cout << "EnergyUsageListener::OnResetCumulativeEnergy()" << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* EnergyUsageCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new EnergyUsageCommands(sample, objectPath);
}

EnergyUsageCommands::EnergyUsageCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

EnergyUsageCommands::~EnergyUsageCommands()
{
}

void EnergyUsageCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ENERGY_USAGE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<EnergyUsageIntfControllee*>(cdmInterface);

        RegisterCommand(&EnergyUsageCommands::OnCmdGetCumulativeEnergy, "eugce", "get cumulative energy");
        RegisterCommand(&EnergyUsageCommands::OnCmdSetCumulativeEnergy, "eusce", "set cumulative energy (use 'eusce <cumulative energy>'");
        RegisterCommand(&EnergyUsageCommands::OnCmdGetPrecision, "eugp", "get precision");
        RegisterCommand(&EnergyUsageCommands::OnCmdSetPrecision, "eusp", "set precision (use 'eusp <precision>'");
        RegisterCommand(&EnergyUsageCommands::OnCmdGetUpdateMinTime, "eugumt", "get update min time");
        RegisterCommand(&EnergyUsageCommands::OnCmdSetUpdateMinTime, "eusumt", "set update min time (use 'eusumt <update min time>'");
    } else {
        PrintCommands();
    }
}

void EnergyUsageCommands::OnCmdGetCumulativeEnergy(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfControllee* intfControllee = static_cast<EnergyUsageCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetCumulativeEnergy() << endl;
}

void EnergyUsageCommands::OnCmdSetCumulativeEnergy(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfControllee* intfControllee = static_cast<EnergyUsageCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double cumulativeEnergy = strtod(cmd.c_str(), NULL);
    intfControllee->SetCumulativeEnergy(cumulativeEnergy);
}

void EnergyUsageCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfControllee* intfControllee = static_cast<EnergyUsageCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetPrecision() << endl;
}

void EnergyUsageCommands::OnCmdSetPrecision(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfControllee* intfControllee = static_cast<EnergyUsageCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double precision = strtod(cmd.c_str(), NULL);
    intfControllee->SetPrecision(precision);
}

void EnergyUsageCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfControllee* intfControllee = static_cast<EnergyUsageCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetUpdateMinTime() << endl;
}

void EnergyUsageCommands::OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfControllee* intfControllee = static_cast<EnergyUsageCommands*>(commands)->GetInterface();

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