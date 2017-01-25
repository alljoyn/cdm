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
#include "OvenCyclePhaseListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus OvenCyclePhaseListener::OnGetCyclePhase(uint8_t& cyclePhase)
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseListener::OnGetCyclePhase" << endl;
    return status;
}

QStatus OvenCyclePhaseListener::OnGetSupportedCyclePhases(OvenCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases)
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseListener::OnGetSupportedCyclePhases" << endl;
    return status;
}

QStatus OvenCyclePhaseListener::OnGetCyclePhasesDescriptions(const qcc::String& language, OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfPhaseDescs, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseListener::OnGetCyclePhasesDescriptions" << endl;
    if(language == "en")
    {
        OvenCyclePhaseInterface::OvenPhaseDescriptor disc;
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