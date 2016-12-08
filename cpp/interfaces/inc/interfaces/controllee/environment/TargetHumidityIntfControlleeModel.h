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

// This file is automatically generated. Do not edit it.

#ifndef TARGETHUMIDITYINTFCONTROLLEELISTENER_H_
#define TARGETHUMIDITYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>
#include <interfaces/common/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity Model Interface class for the Controllee
 */
class TargetHumidityIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of TargetHumidityIntfControlleeModel
     */
    virtual ~TargetHumidityIntfControlleeModel() {}

    /**
     * Get TargetValue
     * @return current target value
     */
    virtual QStatus GetTargetValue(uint8_t& out) const = 0;

     /**
     * Set TargetValue
     * @param[in] value The target value to set
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const uint8_t value) = 0;
    /**
     * Get MinValue
     * @return current min value
     */
    virtual QStatus GetMinValue(uint8_t& out) const = 0;
    /**
     * Get MaxValue
     * @return current max value
     */
    virtual QStatus GetMaxValue(uint8_t& out) const = 0;
    /**
     * Get StepValue
     * @return current step value
     */
    virtual QStatus GetStepValue(uint8_t& out) const = 0;
    /**
     * Get SelectableHumidityLevels
     * @return current selectable humidity levels
     */
    virtual QStatus GetSelectableHumidityLevels(std::vector<uint8_t>& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLEELISTENER_H_ */