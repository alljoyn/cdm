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

#include <iostream>
#include "LaundryCyclePhaseListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus LaundryCyclePhaseListener::OnGetCyclePhase(uint8_t& cyclePhase)
{
    QStatus status = ER_OK;
    cout << "LaundryCyclePhaseListener::OnGetCyclePhase" << endl;
    return status;
}

QStatus LaundryCyclePhaseListener::OnGetSupportedCyclePhases(LaundryCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases)
{
    QStatus status = ER_OK;
    cout << "LaundryCyclePhaseListener::OnGetSupportedCyclePhases" << endl;
    return status;
}

QStatus LaundryCyclePhaseListener::OnGetCyclePhasesDescriptions(const qcc::String& language, LaundryCyclePhaseInterface::CyclePhaseDescriptions& listOfPhaseDescs, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "LaundryCyclePhaseListener::OnGetCyclePhasesDescriptions" << endl;

    if(language == "en")
    {
        LaundryCyclePhaseInterface::LaundryPhaseDescriptor disc;
        disc.phase = 1;
        disc.name = "laundy phase1";
        disc.description = "laundry this is phase 1";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 2;
        disc.name = "laundry phase2";
        disc.description = "laundry this is phase 2";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 3;
        disc.name = "laundry phase3";
        disc.description = "laundry this is phase 3";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 4;
        disc.name = "laundry phase4";
        disc.description = "laundry this is phase 4";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 0x80;
        disc.name = "VendorPhase1";
        disc.description = "this is vendor defined phase 1 for Laundry device";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 0x81;
        disc.name = "VendorPhase2";
        disc.description = "this is vendor defined phase 2 for Laundry device";
        listOfPhaseDescs.push_back(disc);
    }
    else 
    {
        errorCode = LANGUAGE_NOT_SUPPORTED;
        status = ER_LANGUAGE_NOT_SUPPORTED;
    }
    return status;
}



ControlleeCommands* LaundryCyclePhaseCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new LaundryCyclePhaseCommands(sample, objectPath);
}

LaundryCyclePhaseCommands::LaundryCyclePhaseCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

LaundryCyclePhaseCommands::~LaundryCyclePhaseCommands()
{
}

void LaundryCyclePhaseCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(LAUNDRY_CYCLE_PHASE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<LaundryCyclePhaseIntfControllee*>(cdmInterface);

        RegisterCommand(&LaundryCyclePhaseCommands::OnCmdGetCyclePhase, "gcp", "get cycle phase");
        RegisterCommand(&LaundryCyclePhaseCommands::OnCmdSetCyclePhase, "scp", "set cycle phase (use 'sic <cycle phase>')");

        RegisterCommand(&LaundryCyclePhaseCommands::OnCmdGetSupportedCyclePhases, "gscp", "get supported cycle phases");
    } else {
        PrintCommands();
    }
}

void LaundryCyclePhaseCommands::InitializeProperties()
{
    if (m_intfControllee) {
        LaundryCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase = {
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_UNAVAILABLE,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_PRE_WASHING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_WASHING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_RINSING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_SPINNING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_STEAM,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_DRYING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_COOLING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_ANTICREASING,
            0x80 };
        uint8_t cyclePhase = LaundryCyclePhaseInterface::LAUNDRY_PHASE_PRE_WASHING;
        m_intfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_intfControllee->SetCyclePhase(cyclePhase);
    }
}

void LaundryCyclePhaseCommands::OnCmdGetCyclePhase(Commands* commands, std::string& cmd)
{
    cout << "LaundryCyclePhaseCommands::OnCmdGetCyclePhase" << endl;
    LaundryCyclePhaseIntfControllee* intfControllee = static_cast<LaundryCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetCyclePhase() << endl;

}
void LaundryCyclePhaseCommands::OnCmdSetCyclePhase(Commands* commands, std::string& cmd)
{
    cout << "LaundryCyclePhaseCommands::OnCmdSetCyclePhase" << endl;
    LaundryCyclePhaseIntfControllee* intfControllee = static_cast<LaundryCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t cyclePhase = strtol(cmd.c_str(), NULL, 10);
    if(cyclePhase < (uint8_t)LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_UNAVAILABLE ||
       cyclePhase > (uint8_t)LaundryCyclePhaseInterface::LaundryCyclePhase::LAUNDRY_PHASE_ANTICREASING)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetCyclePhase(cyclePhase);

}
void LaundryCyclePhaseCommands::OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd)
{
    cout << "LaundryCyclePhaseCommands::OnCmdGetSupportedCyclePhases" << endl;
    LaundryCyclePhaseIntfControllee* intfControllee = static_cast<LaundryCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const LaundryCyclePhaseInterface::SupportedCyclePhases& supportedPhases = intfControllee->GetSupportedCyclePhases();

    for(size_t i = 0; i < supportedPhases.size(); i++)
        cout << (int)supportedPhases[i] << " ";
    cout << endl;
}