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

#ifndef CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_
#define CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Model Interface class for the Controllee
 */
class ClimateControlModeIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:
    using Mode = ClimateControlModeInterface::Mode;
    using OperationalState = ClimateControlModeInterface::OperationalState;

    /**
     * Destructor of ClimateControlModeIntfControlleeModel
     */
    virtual ~ClimateControlModeIntfControlleeModel() {}

    /**
     * Get Mode
     * @return current mode
     */
    virtual QStatus GetMode(Mode& out) const = 0;

     /**
     * Set Mode
     * @param[in] value The mode to set
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const Mode value) = 0;
    /**
     * Get SupportedModes
     * @return current supported modes
     */
    virtual QStatus GetSupportedModes(std::vector<Mode>& out) const = 0;
    /**
     * Get OperationalState
     * @return current operational state
     */
    virtual QStatus GetOperationalState(OperationalState& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_ */
