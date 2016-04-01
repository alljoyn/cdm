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

#ifndef OVENCYCLEPHASELISTENER_H_
#define OVENCYCLEPHASELISTENER_H_

#include <alljoyn/hae/interfaces/operation/OvenCyclePhaseIntfControlleeListener.h>
using namespace ajn;
using namespace services;


class OvenCyclePhaseListener : public OvenCyclePhaseIntfControlleeListener
{
public:
        virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase);

        virtual QStatus OnGetSupportedCyclePhases(OvenCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases);

        virtual QStatus OnGetCyclePhasesDescriptions(const qcc::String& language,
                                                     OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfPhasesDescs,
                                                     ErrorCode& errorCode);

};

#endif /* OVENCYCLEPHASELISTENER_H_ */
