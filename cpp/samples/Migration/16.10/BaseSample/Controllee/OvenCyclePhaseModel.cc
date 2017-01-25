/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 * Source Project (AJOSP) Contributors and others.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * All rights reserved. This program and the accompanying materials are
 * made available under the terms of the Apache License, Version 2.0
 * which accompanies this distribution, and is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright 2016 Open Connectivity Foundation and Contributors to
 * AllSeen Alliance. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include "OvenCyclePhaseModel.h"
#include "ControlleeSample.h"

using namespace std;

const uint8_t OvenCyclePhaseModel::OVEN_PHASE_COOKING = 0;
const uint8_t OvenCyclePhaseModel::OVEN_PHASE_PREHEATING = 1;
const uint8_t OvenCyclePhaseModel::OVEN_PHASE_CLEANING = 2;
const uint8_t OvenCyclePhaseModel::OVEN_PHASE_UNAVAILABLE = 3;


OvenCyclePhaseModel::OvenCyclePhaseModel()
  : m_cyclePhase(OvenCyclePhaseModel::OVEN_PHASE_PREHEATING)
{
}


QStatus OvenCyclePhaseModel::GetCyclePhase(uint8_t& cyclePhase) const
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseModel::GetCyclePhase" << endl;
    cyclePhase = m_cyclePhase;
    return status;
}


QStatus OvenCyclePhaseModel::GetSupportedCyclePhases(std::vector<uint8_t>& listOfSupportedCyclePhases) const
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseModel::GetSupportedCyclePhases" << endl;
    listOfSupportedCyclePhases = m_listOfSupportedCyclePhases;
    return status;
}


void OvenCyclePhaseModel::SetCyclePhase(uint8_t cyclePhase)
{
    m_cyclePhase = cyclePhase;
}


void OvenCyclePhaseModel::SetSupportedCyclePhases(const std::vector<uint8_t> listOfSupportedCyclePhases)
{
    m_listOfSupportedCyclePhases = listOfSupportedCyclePhases;
}

QStatus OvenCyclePhaseModel::GetVendorPhasesDescription(qcc::String& language, std::vector<OvenCyclePhaseInterface::CyclePhaseDescriptor>& listOfPhaseDescs, ErrorCode& errorCode, CdmControllee& controllee)
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseModel::OnGetCyclePhasesDescriptions" << endl;
    if(language == "en")
    {
        OvenCyclePhaseInterface::CyclePhaseDescriptor disc;
        disc.phase = 1;
        disc.name = "Oven phase1";
        disc.description = "Oven this is phase 1";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 2;
        disc.name = "Oven phase2";
        disc.description = "Oven this is phase 2";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 3;
        disc.name = "Oven phase3";
        disc.description = "Oven this is phase 3";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 4;
        disc.name = "Oven phase4";
        disc.description = "Oven this is phase 4";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 0x80;
        disc.name = "VendorPhase1";
        disc.description = "this is vendor defined phase 1 for Oven";
        listOfPhaseDescs.push_back(disc);

        disc.phase = 0x81;
        disc.name = "VendorPhase1";
        disc.description = "this is vendor defined phase 1 for Oven";
        listOfPhaseDescs.push_back(disc);
    }
    else
    {
        errorCode = LANGUAGE_NOT_SUPPORTED;
        return ER_LANGUAGE_NOT_SUPPORTED;
    }
    return status;
}