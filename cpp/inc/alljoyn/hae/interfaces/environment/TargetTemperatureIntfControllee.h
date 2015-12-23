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

#ifndef TARGETTEMPERATUREINTFCONTROLLEE_H_
#define TARGETTEMPERATUREINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature Interface Controllee class
 */
class TargetTemperatureIntfControllee : public TargetTemperatureInterface {
  public:
    /**
     * Constructor of TargetTemperatureIntfControllee
     */
    TargetTemperatureIntfControllee() {}

    /**
     * Destructor of TargetTemperatureIntfControllee
     */
    virtual ~TargetTemperatureIntfControllee() {}

    /**
     * Get target temperature
     * @return Target temperature
     */
    virtual const double GetTargetValue() const = 0;

    /**
     * Set target temperature
     * @param[in] TargetTemperature the target temperature
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const double TargetTemperature) = 0;

    /**
     * Get the minimum value of target temperature
     * @return The minimum value of target temperature
     */
    virtual const double GetMinValue() const = 0;

    /**
     * Set the minimum value of target temperature
     * @param[in] value the minimum value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus SetMinValue(const double value) = 0;

    /**
     * Get the maximum value of target temperature
     * @return The maximum value of target temperature
     */
    virtual const double GetMaxValue() const = 0;
    /**
     * Set the maximum value of target temperature
     * @param[in] value the maximum value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus SetMaxValue(const double value) = 0;

    /**
     * Get the step value of target temperature
     * @return The step value of target temperature
     */
    virtual const double GetStepValue() const = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEE_H_ */
