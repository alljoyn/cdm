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
#include "LaundryCyclePhaseListener.h"

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

    return status;
}
