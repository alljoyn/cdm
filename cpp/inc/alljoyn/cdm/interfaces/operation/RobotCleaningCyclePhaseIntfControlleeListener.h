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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include "RobotCleaningCyclePhaseInterface.h"

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface Controllee Listener class
 */
class RobotCleaningCyclePhaseIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RobotCleaningCyclePhaseIntfControlleeListener
     */
    virtual ~RobotCleaningCyclePhaseIntfControlleeListener() {}

    /**
     * Handler for getting CyclePhase property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] cyclePhase cycle phase
     * @return ER_OK on success
     */
    virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase) = 0;

    /**
     * Handler for getting SupportedCyclePhases property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedCyclePhases supported cycle phases
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedCyclePhases(RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases) = 0;

    /**
     * Handler for GetVendorPhasesDescription method
     * @param[in] languageTag language tag
     * @param[out] phasesDescription the list of cycle phases description
     * @param[out] errorCode the error code should be set when the method call is failed
     * @return ER_OK on succes
     */
    virtual QStatus OnGetVendorPhasesDescription(const qcc::String& languageTag,
                                                 RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                 ErrorCode& errorCode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_ */
