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

#ifndef TARGETHUMIDITYINTFCONTROLLEE_H_
#define TARGETHUMIDITYINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity Interface Controllee class
 */
class TargetHumidityIntfControllee : public TargetHumidityInterface {
  public:
    typedef enum {
        ROUNDING_TO_NEAREST_VALUE,
        ROUNDING_OFF,
        ROUNDING_UP
    } AdjustStrategy;

    /**
     * Constructor of TargetHumidityIntfControllee
     */
    TargetHumidityIntfControllee() {}

    /**
     * Destructor of TargetHumidityIntfControllee
     */
    virtual ~TargetHumidityIntfControllee() {}

    /**
     * Get target humidity
     * @return Target humidity
     */
    virtual const uint8_t GetTargetValue() const = 0;

    /**
     * Set target humidity
     * @param[in] TargetHumidity the target humidity
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const uint8_t TargetHumidity) = 0;

    /**
     * Get the minimum value of target humidity
     * @return The minimum value of target humidity
     */
    virtual const uint8_t GetMinValue() const = 0;

    /**
     * Set the minimum value of target humidity
     * @param[in] value the minimum value of target humidity
     * @return ER_OK on success
     */
    virtual QStatus SetMinValue(const uint8_t value) = 0;

    /**
     * Get the maximum value of target humidity
     * @return The maximum value of target humidity
     */
    virtual const uint8_t GetMaxValue() const = 0;

    /**
     * Set the maximum value of target humidity
     * @param[in] value the maximum value of target humidity
     * @return ER_OK on success
     */
    virtual QStatus SetMaxValue(const uint8_t value) = 0;

    /**
     * Get the step value of target humidity
     * @return The step value of target humidity
     */
    virtual const uint8_t GetStepValue() const = 0;

    /**
     * Set the step value of target humidity
     * @param[in] value the step value of target humidity
     * @return ER_OK on success
     */
    virtual QStatus SetStepValue(const uint8_t value) = 0;

    /**
     * Get the selectable humidity levels
     * @return The selectable humidity levels
     */
    virtual const TargetHumidityInterface::HumidityLevels& GetSelectableHumidityLevels() const = 0;

    /**
     * Set the selectable humidity levels
     * @param[in] value the selectable humidity levels
     * @return ER_OK on success
     */
    virtual QStatus SetSelectableHumidityLevels(const TargetHumidityInterface::HumidityLevels& value) = 0;

    /**
     * Set strategy of adjusting target value
     * @param[in] strategy
     * @return status
     */
    virtual QStatus SetStrategyOfAdjustingTargetValue(AdjustStrategy strategy) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLEE_H_ */
