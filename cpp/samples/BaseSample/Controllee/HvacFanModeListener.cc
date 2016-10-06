/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "HvacFanModeListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus HvacFanModeListener::OnSetMode(const uint16_t& mode)
{
    cout << "HvacFanModeListener::OnSetMode() - Mode : " << mode << endl;
    return ER_OK;
}

QStatus HvacFanModeListener::OnGetMode(uint16_t& mode)
{
    cout << "HvacFanModeListener::OnGetMode() - Mode : " << mode << endl;
    return ER_OK;
}

QStatus HvacFanModeListener::OnGetSupportedModes(SupportedModes& modes)
{
    cout << "HvacFanModeListener::OnGetSupportedModes() - modes : ";

    for(size_t i=0 ; i < modes.size() ; i++)
    {
        cout << modes[i] << " ";
    }
    cout << endl;

    return ER_OK;
}

////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* HvacFanModeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new HvacFanModeCommands(sample, objectPath);
}

HvacFanModeCommands::HvacFanModeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

HvacFanModeCommands::~HvacFanModeCommands()
{
}

void HvacFanModeCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(HVAC_FAN_MODE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<HvacFanModeIntfControllee*>(cdmInterface);

        RegisterCommand(&HvacFanModeCommands::OnCmdGetMode, "ccmgm", "get mode");
        RegisterCommand(&HvacFanModeCommands::OnCmdSetMode, "ccmsm", "set mode (use 'ccmsm <mode>'");
        RegisterCommand(&HvacFanModeCommands::OnCmdGetSupportedModes, "ccmgsm", "get supported modes");
    } else {
        PrintCommands();
    }
}

void HvacFanModeCommands::InitializeProperties()
{
    if (m_intfControllee) {
        HvacFanModeInterface::SupportedModes supportedModes;
        supportedModes.push_back(HvacFanModeInterface::HVAC_FAN_MODE_AUTO);
        supportedModes.push_back(HvacFanModeInterface::HVAC_FAN_MODE_CIRCULATION);
        supportedModes.push_back(HvacFanModeInterface::HVAC_FAN_MODE_CONTINUOUS);
        m_intfControllee->SetSupportedModes(supportedModes);
        m_intfControllee->SetMode(HvacFanModeInterface::HVAC_FAN_MODE_AUTO);
    }
}

void HvacFanModeCommands::OnCmdGetMode(Commands* commands, std::string& cmd)
{
    HvacFanModeIntfControllee* intfControllee = static_cast<HvacFanModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMode() << endl;
}

void HvacFanModeCommands::OnCmdSetMode(Commands* commands, std::string& cmd)
{
    HvacFanModeIntfControllee* intfControllee = static_cast<HvacFanModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode < HvacFanModeInterface::MIN_HVAC_FAN_MODE || mode > HvacFanModeInterface::MAX_HVAC_FAN_MODE) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetMode((uint16_t)mode);
}

void HvacFanModeCommands::OnCmdGetSupportedModes(Commands* commands, std::string& cmd)
{
    HvacFanModeIntfControllee* intfControllee = static_cast<HvacFanModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const HvacFanModeInterface::SupportedModes& supportedModes = intfControllee->GetSupportedModes();
    for(HvacFanModeInterface::SupportedModes::const_iterator citr = supportedModes.begin();
        citr != supportedModes.end(); citr++) {
        cout << *citr << " ";
    }
    cout << endl;
}