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

#include "ClimateControlModeListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus ClimateControlModeListener::OnSetMode(const uint16_t& mode)
{
    cout << "ClimateControlModeListener::OnSetMode() - Mode : " << mode << endl;
    return ER_OK;
}

QStatus ClimateControlModeListener::OnGetMode(uint16_t& mode)
{
    cout << "ClimateControlModeListener::OnGetMode() - Mode : " << mode << endl;
    return ER_OK;
}

QStatus ClimateControlModeListener::OnGetSupportedModes(SupportedModes& modes)
{
    cout << "ClimateControlModeListener::OnGetSupportedModes() - modes : ";

    for(size_t i=0 ; i < modes.size() ; i++)
    {
        cout << modes[i] << " ";
    }
    cout << endl;

    return ER_OK;
}

QStatus ClimateControlModeListener::OnGetOperationalState(uint16_t& operationalState)
{
    cout << "ClimateControlModeListener::OnGetOperationalState() - operationalState : " << operationalState << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* ClimateControlModeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new ClimateControlModeCommands(sample, objectPath);
}

ClimateControlModeCommands::ClimateControlModeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

ClimateControlModeCommands::~ClimateControlModeCommands()
{
}

void ClimateControlModeCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CLIMATE_CONTROL_MODE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<ClimateControlModeIntfControllee*>(cdmInterface);

        RegisterCommand(&ClimateControlModeCommands::OnCmdGetMode, "ccmgm", "get mode");
        RegisterCommand(&ClimateControlModeCommands::OnCmdSetMode, "ccmsm", "set mode (use 'ccmsm <mode>'");
        RegisterCommand(&ClimateControlModeCommands::OnCmdGetSupportedModes, "ccmgsm", "get supported modes");
        RegisterCommand(&ClimateControlModeCommands::OnCmdGetOperationalState, "ccmgos", "get operational state");
        RegisterCommand(&ClimateControlModeCommands::OnCmdSetOperationalState, "ccmsos", "set operational state (use 'ccmsos <operational state>'");
    } else {
        PrintCommands();
    }
}

void ClimateControlModeCommands::InitializeProperties()
{
    if (m_intfControllee) {
        ClimateControlModeInterface::SupportedModes supportedModes;
        supportedModes.push_back(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_OFF);
        supportedModes.push_back(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_HEAT);
        supportedModes.push_back(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_COOL);
        supportedModes.push_back(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_DRY);
        m_intfControllee->SetSupportedModes(supportedModes);
        m_intfControllee->SetMode(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_OFF);
        m_intfControllee->SetOperationalState(ClimateControlModeInterface::CLIMATE_CONTROL_OPERATIONAL_STATE_IDLE);
    }
}

void ClimateControlModeCommands::OnCmdGetMode(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfControllee* intfControllee = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMode() << endl;
}

void ClimateControlModeCommands::OnCmdSetMode(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfControllee* intfControllee = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode < ClimateControlModeInterface::MIN_CLIMATE_CONTROL_MODE || mode > ClimateControlModeInterface::MAX_CLIMATE_CONTROL_MODE) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetMode((uint16_t)mode);
}

void ClimateControlModeCommands::OnCmdGetSupportedModes(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfControllee* intfControllee = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const ClimateControlModeInterface::SupportedModes& supportedModes = intfControllee->GetSupportedModes();
    for(ClimateControlModeInterface::SupportedModes::const_iterator citr = supportedModes.begin();
        citr != supportedModes.end(); citr++) {
        cout << *citr << " ";
    }
    cout << endl;
}

void ClimateControlModeCommands::OnCmdGetOperationalState(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfControllee* intfControllee = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetOperationalState() << endl;
}

void ClimateControlModeCommands::OnCmdSetOperationalState(Commands* commands, std::string& cmd)
{
    ClimateControlModeIntfControllee* intfControllee = static_cast<ClimateControlModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int operationalState = strtol(cmd.c_str(), NULL, 10);
    if (operationalState < ClimateControlModeInterface::MIN_CLIMATE_CONTROL_OPERATIONAL_STATE
        || operationalState > ClimateControlModeInterface::MAX_CLIMATE_CONTROL_OPERATIONAL_STATE) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetOperationalState((uint16_t)operationalState);
}