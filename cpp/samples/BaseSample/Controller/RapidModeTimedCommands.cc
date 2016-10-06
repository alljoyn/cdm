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

#include "RapidModeTimedCommands.h"
#include "ControllerSample.h"

RapidModeTimedListener::RapidModeTimedListener()
{
}

RapidModeTimedListener::~RapidModeTimedListener()
{
}

void RapidModeTimedListener::OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "RapidModeMinutesRemaining: " << value << endl;
}

void RapidModeTimedListener::OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "RapidModeMinutesRemaining: " << value << endl;
}

void RapidModeTimedListener::OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void RapidModeTimedListener::OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxSetMinutes: " << value << endl;
}


RapidModeTimedCommands::RapidModeTimedCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

RapidModeTimedCommands::~RapidModeTimedCommands()
{

}

void RapidModeTimedCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(RAPID_MODE_TIMED_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<RapidModeTimedIntfController*>(cdmInterface);
    }

    RegisterCommand(&RapidModeTimedCommands::OnCmdGetRapidModeMinutesRemaining, "grmmr", "get rapid mode minutes remaining");
    RegisterCommand(&RapidModeTimedCommands::OnCmdSetRapidModeMinutesRemaining, "srmmr", "set rapid mode minutes remaining (use 'srmmr <value>'");
    RegisterCommand(&RapidModeTimedCommands::OnCmdGetMaxSetMinutes, "gmsm", "get max set minutes");
    PrintCommands();
}

void RapidModeTimedCommands::OnCmdGetRapidModeMinutesRemaining(Commands* commands, std::string& cmd)
{
    RapidModeTimedIntfController* intfController = static_cast<RapidModeTimedCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetRapidModeMinutesRemaining();
}

void RapidModeTimedCommands::OnCmdSetRapidModeMinutesRemaining(Commands* commands, std::string& cmd)
{
    RapidModeTimedIntfController* intfController = static_cast<RapidModeTimedCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 || value >= 65536) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetRapidModeMinutesRemaining((uint16_t)value);
}

void RapidModeTimedCommands::OnCmdGetMaxSetMinutes(Commands* commands, std::string& cmd)
{
    RapidModeTimedIntfController* intfController = static_cast<RapidModeTimedCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxSetMinutes();
}