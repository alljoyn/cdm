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

#include <iostream>
#include "TimeDisplayListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus TimeDisplayListener::OnGetDisplayTimeFormat(uint8_t& timeFormat)
{
    cout << " TimeDisplayListener::OnGetDisplayTimeFormat" << endl;
    return ER_OK;
}

QStatus TimeDisplayListener::OnSetDisplayTimeFormat(const uint8_t timeFormat)
{
    cout << " TimeDisplayListener::OnSetDisplayTimeFormat" << endl;
    return ER_OK;
}

QStatus TimeDisplayListener::OnGetSupportedDisplayTimeFormats(std::vector<uint8_t>& supportedTimeFormats)
{
    cout << " TimeDisplayListener::OnGetSupportedDisplayTimeFormats" << endl;
    return ER_OK;
}

QStatus TimeDisplayListener::OnSetSupportedDisplayTimeFormats(const std::vector<uint8_t>& supportedTimeFormats)
{
    cout << " TimeDisplayListener::OnSetSupportedDisplayTimeFormats" << endl;
    return ER_OK;
}


ControlleeCommands* TimeDisplayCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new TimeDisplayCommands(sample, objectPath);
}

TimeDisplayCommands::TimeDisplayCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

TimeDisplayCommands::~TimeDisplayCommands()
{
}

void TimeDisplayCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TIME_DISPLAY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<TimeDisplayIntfControllee*>(cdmInterface);

        RegisterCommand(&TimeDisplayCommands::OnCmdGetDisplayTimeFormat, "gdtf", "get display time format");
        RegisterCommand(&TimeDisplayCommands::OnCmdSetDisplayTimeFormat, "sdtf", "set display time format (use 'sdtf <0 - 12 h format / 1 -24 h format>')");


        RegisterCommand(&TimeDisplayCommands::OnCmdGetSupportedDisplayTimeFormats, "gsdtf", "get supported display time formats");
    } else {
        PrintCommands();
    }
}

void TimeDisplayCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t timeFormat = 6;
        std::vector<uint8_t> supportedTimeFormats;

        supportedTimeFormats.push_back(0);
        supportedTimeFormats.push_back(1);

        m_intfControllee->SetDisplayTimeFormat(timeFormat);
        m_intfControllee->SetSupportedDisplayTimeFormats(supportedTimeFormats);
    }
}

void TimeDisplayCommands::OnCmdGetDisplayTimeFormat(Commands* commands, std::string& cmd)
{
    cout << "TimeDisplayCommands::OnCmdGetDisplayTimeFormat" << endl;
    TimeDisplayIntfControllee* intfControllee = static_cast<TimeDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetDisplayTimeFormat() << endl;
}
void TimeDisplayCommands::OnCmdSetDisplayTimeFormat(Commands* commands, std::string& cmd)
{
    cout << "TimeDisplayCommands::OnCmdSetDisplayTimeFormat" << endl;
    TimeDisplayIntfControllee* intfControllee = static_cast<TimeDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t timeFormat = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetDisplayTimeFormat(timeFormat);
}

void TimeDisplayCommands::OnCmdGetSupportedDisplayTimeFormats(Commands* commands, std::string& cmd)
{
    cout << "TimeDisplayCommands::OnCmdGetSupportedDisplayTimeFormats" << endl;
    TimeDisplayIntfControllee* intfControllee = static_cast<TimeDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const std::vector<uint8_t> supportedTimeFormats = intfControllee->GetSupportedDisplayTimeFormats();

    for(size_t i = 0; i < supportedTimeFormats.size(); i++)
        cout << (int)supportedTimeFormats[i] << " ";
    cout << endl;
}