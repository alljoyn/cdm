/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef TARGETTEMPERATUREINTFCONTROLLEE_H_
#define TARGETTEMPERATUREINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature Interface Controllee class
 */
class TargetTemperatureIntfControllee : public TargetTemperatureInterface {
  public:
    typedef enum {
        ROUNDING_TO_NEAREST_VALUE,
        ROUNDING_OFF,
        ROUNDING_UP
    } AdjustTargetValue;

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

    /**
     * Set the step value of target temperature
     * @param[in] value the step value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus SetStepValue(const double value) = 0;

    /**
     * Set strategy of adjusting target value
     * @param[in] strategy
     * @return status
     */
    virtual QStatus SetStrategyOfAdjustingTargetValue(AdjustTargetValue strategy) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEE_H_ */