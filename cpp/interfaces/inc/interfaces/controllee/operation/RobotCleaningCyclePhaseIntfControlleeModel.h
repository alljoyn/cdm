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
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/RobotCleaningCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Model Interface class for the Controllee
 */
class RobotCleaningCyclePhaseIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:
    using CyclePhaseDescriptor = RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor;

    /**
     * Destructor of RobotCleaningCyclePhaseIntfControlleeModel
     */
    virtual ~RobotCleaningCyclePhaseIntfControlleeModel() {}

    /**
     * Get CyclePhase
     * @return current cycle phase
     */
    virtual QStatus GetCyclePhase(uint8_t& out) const = 0;
    /**
     * Get SupportedCyclePhases
     * @return current supported cycle phases
     */
    virtual QStatus GetSupportedCyclePhases(std::vector<uint8_t>& out) const = 0;

    /**
     * Handler for method GetVendorPhasesDescription
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus GetVendorPhasesDescription(qcc::String arg_languageTag, std::vector<CyclePhaseDescriptor>& arg_phasesDescription, ErrorCode& error, CdmSideEffects& sideEffects) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_ */
