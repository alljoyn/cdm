/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include "OvenCyclePhaseListener.h"

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

QStatus OvenCyclePhaseListener::OnGetCyclePhasesDescriptions(const qcc::String language, OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfPhaseDescs, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "OvenCyclePhaseListener::OnGetCyclePhasesDescriptions" << endl;

    OvenCyclePhaseInterface::OvenPhaseDescriptor disc;
    disc.phase = 0x80;
    disc.name = "VendorPhase1";
    disc.description = "this is vendor defined phase 1 for Oven";
    listOfPhaseDescs.push_back(disc);

    disc.phase = 0x81;
    disc.name = "VendorPhase1";
    disc.description = "this is vendor defined phase 1 for Oven";
    listOfPhaseDescs.push_back(disc);

    return status;
}