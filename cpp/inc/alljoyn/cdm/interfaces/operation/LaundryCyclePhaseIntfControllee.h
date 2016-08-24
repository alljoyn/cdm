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

#ifndef LAUNDRYCYCLEPHASEINTFCONTROLLEE_H_
#define LAUNDRYCYCLEPHASEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * LaundryCyclePhase Interface Controllee class
 */
class LaundryCyclePhaseIntfControllee : public LaundryCyclePhaseInterface {
  public:
    /**
     * Constructor of LaundryCyclePhaseIntfControllee
     */
    LaundryCyclePhaseIntfControllee() {}

    /**
     * Destructor of LaundryCyclePhaseIntfControllee
     */
    virtual ~LaundryCyclePhaseIntfControllee() {}

    /**
     * Get CyclePhase
     * @return current cycle phase
     */
    virtual const uint8_t GetCyclePhase() const = 0;

    /**
     * Set CyclePhase
     * @param[in]  cyclePhase the cycle phase to set
     * @return ER_OK on success
     */
    virtual QStatus SetCyclePhase(const uint8_t cyclePhase) = 0;

    /**
     * Get SupportedCyclePhases
     * @return the list of supported cycle phases
     */
    virtual const SupportedCyclePhases& GetSupportedCyclePhases() const = 0;

    /**
     * Set OperationalState
     * @param[in]  supportedCyclePhases the list of supported cycle phases to set
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedCyclePhases(const SupportedCyclePhases& supportedCyclePhases) = 0;

    /**
     * Set VendorDefinedCyclePhases
     * @param[in]  vendorPhases the list of vendor defined cycle phases to set
     * @return ER_OK on success
     */
    virtual QStatus SetVendorDefinedCyclePhases(const std::vector<uint8_t>& vendorPhases) = 0;

};

} //namespace services
} //namespace ajn

#endif /* LAUNDRYCYCLEPHASEINTFCONTROLLEE_H_ */
