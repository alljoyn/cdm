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
#include "RobotCleaningCyclePhaseListener.h"

using namespace std;

QStatus RobotCleaningCyclePhaseListener::OnGetCyclePhase(uint8_t& cyclePhase)
{
    cout << "RobotCleaningCyclePhaseListener::OnGetCyclePhase()" << endl;
    return ER_OK;
}

QStatus RobotCleaningCyclePhaseListener::OnGetSupportedCyclePhases(RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases)
{
    cout << "RobotCleaningCyclePhaseListener::OnGetSupportedCyclePhases()" << endl;
    return ER_OK;
}

QStatus RobotCleaningCyclePhaseListener::OnGetVendorPhasesDescription(const qcc::String& languageTag,
                                                                      RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                                      ErrorCode& errorCode)
{
    cout << "RobotCleaningCyclePhaseListener::OnGetVendorPhasesDescription" << endl;

    if (languageTag == "en") {
        RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors description;
        RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor descriptor1;
        descriptor1.phase = 0x80;
        descriptor1.name = "Paused";
        descriptor1.description = "Paused state";
        description.push_back(descriptor1);
        phasesDescription = description;
    } else {
        errorCode = LANGUAGE_NOT_SUPPORTED;
        return ER_LANGUAGE_NOT_SUPPORTED;
    }

    return ER_OK;
}
