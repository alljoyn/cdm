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

#include "RapidModeTimedListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus RapidModeTimedListener::OnGetRapidModeMinutesRemaining(uint16_t& value)
{
    cout << "RapidModeTimedListener::OnGetRapidModeMinutesRemaining()" << endl;
    return ER_OK;
}

QStatus RapidModeTimedListener::OnSetRapidModeMinutesRemaining(const uint16_t& value)
{
    cout << "RapidModeTimedListener::OnSetRapidModeMinutesRemaining() - RapidModeMinutesRemaining : " << value << endl;
    return ER_OK;
}

QStatus RapidModeTimedListener::OnGetMaxSetMinutes(uint16_t& value)
{
    cout << "RapidModeTimedListener::OnGetMaxSetMinutes()" << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* RapidModeTimedCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new RapidModeTimedCommands(sample, objectPath);
}

RapidModeTimedCommands::RapidModeTimedCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

RapidModeTimedCommands::~RapidModeTimedCommands()
{
}

void RapidModeTimedCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(RAPID_MODE_TIMED_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<RapidModeTimedIntfControllee*>(cdmInterface);

        RegisterCommand(&RapidModeTimedCommands::OnCmdGetRapidModeMinutesRemaining, "grmmr", "get rapid mode minutes remaining");
        RegisterCommand(&RapidModeTimedCommands::OnCmdSetRapidModeMinutesRemaining, "srmmr", "set rapid mode minutes remaining (use 'srmmr <value>'");
        RegisterCommand(&RapidModeTimedCommands::OnCmdGetMaxSetMinutes, "gmsm", "get max minutes");

        return;
    } else {
        PrintCommands();
    }
}

void RapidModeTimedCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint16_t maxSetMinutes = 60;
        uint16_t rapidModeMinutesRemaining = 30;

        m_intfControllee->SetMaxSetMinutes(maxSetMinutes);
        m_intfControllee->SetRapidModeMinutesRemaining(rapidModeMinutesRemaining);
    }
}

void RapidModeTimedCommands::OnCmdGetRapidModeMinutesRemaining(Commands* commands, std::string& cmd)
{
    RapidModeTimedIntfControllee* intfControllee = static_cast<RapidModeTimedCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetRapidModeMinutesRemaining() << endl;
}

void RapidModeTimedCommands::OnCmdSetRapidModeMinutesRemaining(Commands* commands, std::string& cmd)
{
    RapidModeTimedIntfControllee* intfControllee = static_cast<RapidModeTimedCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 || value >= 65536) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetRapidModeMinutesRemaining((uint16_t)value);
}

void RapidModeTimedCommands::OnCmdGetMaxSetMinutes(Commands* commands, std::string& cmd)
{
    RapidModeTimedIntfControllee* intfControllee = static_cast<RapidModeTimedCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMaxSetMinutes() << endl;
}