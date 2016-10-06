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
#include "DishWashingCyclePhaseListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus DishWashingCyclePhaseListener::OnGetCyclePhase(uint8_t& cyclePhase)
{
    QStatus status = ER_OK;
    cout << "DishWashingCyclePhaseListener::OnGetCyclePhase" << endl;
    return status;
}

QStatus DishWashingCyclePhaseListener::OnGetSupportedCyclePhases(DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases)
{
    QStatus status = ER_OK;
    cout << "DishWashingCyclePhaseListener::OnGetSupportedCyclePhases" << endl;
    return status;
}

QStatus DishWashingCyclePhaseListener::OnGetCyclePhasesDescriptions(const qcc::String& language, DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfPhaseDescs, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "DishWashingCyclePhaseListener::OnGetCyclePhasesDescriptions" << endl;
    if(language == "en")
    {
        DishWashingCyclePhaseInterface::DishWashingPhaseDescriptor disc;
        disc.phase = 1;
        disc.name = "phase1";
        disc.description = "this is phase 1";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 2;
        disc.name = "phase2";
        disc.description = "this is phase 2";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 3;
        disc.name = "phase3";
        disc.description = "this is phase 3";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 4;
        disc.name = "phase4";
        disc.description = "this is phase 4";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 0x80;
        disc.name = "VendorPhase1";
        disc.description = "this is vendor defined phase 1 for dish washer";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 0x81;
        disc.name = "VendorPhase2";
        disc.description = "this is vendor defined phase 2 dish washer";
        listOfPhaseDescs.push_back(disc);
    }
    else 
    {
        errorCode = LANGUAGE_NOT_SUPPORTED;
        status = ER_LANGUAGE_NOT_SUPPORTED;
    }
    return status;
}


ControlleeCommands* DishWashingCyclePhaseCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new DishWashingCyclePhaseCommands(sample, objectPath);
}

DishWashingCyclePhaseCommands::DishWashingCyclePhaseCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

DishWashingCyclePhaseCommands::~DishWashingCyclePhaseCommands()
{
}

void DishWashingCyclePhaseCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(DISH_WASHING_CYCLE_PHASE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<DishWashingCyclePhaseIntfControllee*>(cdmInterface);

        RegisterCommand(&DishWashingCyclePhaseCommands::OnCmdGetCyclePhase, "gcp", "get cycle phase");
        RegisterCommand(&DishWashingCyclePhaseCommands::OnCmdSetCyclePhase, "scp", "set cycle phase (use 'sic <cycle phase>')");

        RegisterCommand(&DishWashingCyclePhaseCommands::OnCmdGetSupportedCyclePhases, "gscp", "get supported cycle phases");
    } else {
        PrintCommands();
    }
}

void DishWashingCyclePhaseCommands::InitializeProperties()
{
    if (m_intfControllee) {
        DishWashingCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase = {
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_UNAVAILABLE,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_PRE_WASH,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_WASH,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_RINSE,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_DRY,
            0x80 };
        uint8_t cyclePhase = DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_PRE_WASH;
        m_intfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_intfControllee->SetCyclePhase(cyclePhase);
    }
}

void DishWashingCyclePhaseCommands::OnCmdGetCyclePhase(Commands* commands, std::string& cmd)
{
    cout << "DishWashingCyclePhaseCommands::OnCmdGetCyclePhase" << endl;
    DishWashingCyclePhaseIntfControllee* intfControllee = static_cast<DishWashingCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetCyclePhase() << endl;

}
void DishWashingCyclePhaseCommands::OnCmdSetCyclePhase(Commands* commands, std::string& cmd)
{
    cout << "DishWashingCyclePhaseCommands::OnCmdSetCyclePhase" << endl;
    DishWashingCyclePhaseIntfControllee* intfControllee = static_cast<DishWashingCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t cyclePhase = strtol(cmd.c_str(), NULL, 10);
    if(cyclePhase < (uint8_t)DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_UNAVAILABLE ||
       cyclePhase > (uint8_t)DishWashingCyclePhaseInterface::DishWashingCyclePhase::DISH_WASHING_PHASE_DRY)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetCyclePhase(cyclePhase);

}
void DishWashingCyclePhaseCommands::OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd)
{
    cout << "DishWashingCyclePhaseCommands::OnCmdGetSupportedCyclePhases" << endl;
    DishWashingCyclePhaseIntfControllee* intfControllee = static_cast<DishWashingCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const DishWashingCyclePhaseInterface::SupportedCyclePhases& supportedPhases = intfControllee->GetSupportedCyclePhases();

    for(size_t i = 0; i < supportedPhases.size(); i++)
        cout << (int)supportedPhases[i] << " ";
    cout << endl;
}