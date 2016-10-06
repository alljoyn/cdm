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

#include "CurrentPowerListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus CurrentPowerListener::OnSetCurrentPower(const double currentPower)
{
    cout << "CurrentPowerListener::OnSetCurrentPower() - CurrentPower : " << currentPower << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnGetCurrentPower(double& currentPower)
{
    cout << "CurrentPowerListener::OnGetCurrentPower() - CurrentPower : " << currentPower << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnSetPrecision(const double precision)
{
    cout << "CurrentPowerListener::OnSetPrecision() - precision : " << precision << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnGetPrecision(double& precision)
{
    cout << "CurrentPowerListener::OnGetPrecision() - precision : " << precision << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnSetUpdateMinTime(const uint16_t updateMinTime)
{
    cout << "CurrentPowerListener::OnSetUpdateMinTime() - updateMinTime) : " << updateMinTime << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnGetUpdateMinTime(uint16_t& updateMinTime)
{
    cout << "CurrentPowerListener::OnGetUpdateMinTime() - updateMinTime : " << updateMinTime << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* CurrentPowerCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new CurrentPowerCommands(sample, objectPath);
}

CurrentPowerCommands::CurrentPowerCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

CurrentPowerCommands::~CurrentPowerCommands()
{
}

void CurrentPowerCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_POWER_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<CurrentPowerIntfControllee*>(cdmInterface);

        RegisterCommand(&CurrentPowerCommands::OnCmdGetCurrentPower, "cpgcp", "get current power");
        RegisterCommand(&CurrentPowerCommands::OnCmdSetCurrentPower, "cpscp", "set current power (use 'cpscp <power>'");
        RegisterCommand(&CurrentPowerCommands::OnCmdGetPrecision, "cpgp", "get precision");
        RegisterCommand(&CurrentPowerCommands::OnCmdSetPrecision, "cpsp", "set precision (use 'cpsp <precision>'");
        RegisterCommand(&CurrentPowerCommands::OnCmdGetUpdateMinTime, "cpgumt", "get update min time");
        RegisterCommand(&CurrentPowerCommands::OnCmdSetUpdateMinTime, "cpsumt", "set update min time (use 'cpsumt <update min time>'");
    } else {
        PrintCommands();
    }
}

void CurrentPowerCommands::OnCmdGetCurrentPower(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfControllee* intfControllee = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetCurrentPower() << endl;
}

void CurrentPowerCommands::OnCmdSetCurrentPower(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfControllee* intfControllee = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double power = strtod(cmd.c_str(), NULL);
    intfControllee->SetCurrentPower(power);
}

void CurrentPowerCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfControllee* intfControllee = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetPrecision() << endl;
}

void CurrentPowerCommands::OnCmdSetPrecision(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfControllee* intfControllee = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double precision = strtod(cmd.c_str(), NULL);
    intfControllee->SetPrecision(precision);
}

void CurrentPowerCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfControllee* intfControllee = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetUpdateMinTime() << endl;
}

void CurrentPowerCommands::OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentPowerIntfControllee* intfControllee = static_cast<CurrentPowerCommands*>(commands)->GetInterface();

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
