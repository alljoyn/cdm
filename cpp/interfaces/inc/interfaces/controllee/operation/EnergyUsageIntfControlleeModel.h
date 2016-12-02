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

#ifndef ENERGYUSAGEINTFCONTROLLEELISTENER_H_
#define ENERGYUSAGEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/EnergyUsageInterface.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Model Interface class for the Controllee
 */
class EnergyUsageIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of EnergyUsageIntfControlleeModel
     */
    virtual ~EnergyUsageIntfControlleeModel() {}

    /**
     * Get CumulativeEnergy
     * @return current cumulative energy
     */
    virtual QStatus GetCumulativeEnergy(double& out) const = 0;
    /**
     * Get Precision
     * @return current precision
     */
    virtual QStatus GetPrecision(double& out) const = 0;
    /**
     * Get UpdateMinTime
     * @return current update min time
     */
    virtual QStatus GetUpdateMinTime(uint16_t& out) const = 0;

    /**
     * Handler for method ResetCumulativeEnergy
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus ResetCumulativeEnergy(ErrorCode& error, CdmSideEffects& sideEffects) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLEELISTENER_H_ */
