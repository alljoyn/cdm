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

#ifndef CURRENTTEMPERATUREINTFCONTROLLEE_H_
#define CURRENTTEMPERATUREINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentTemperature Interface Controllee class
 */
class CurrentTemperatureIntfControllee : public CurrentTemperatureInterface {
  public:
    /**
     * Constructor of CurrentTemperatureIntfControllee
     */
    CurrentTemperatureIntfControllee() {}

    /**
     * Destructor of CurrentTemperatureIntfControllee
     */
    virtual ~CurrentTemperatureIntfControllee() {}

    /**
     * Get current temperature
     * @return Current temperature
     */
    virtual const double GetCurrentValue() const = 0;

    /**
     * Set current temperature
     * @param[in] value current temperature
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentValue(const double value) = 0;

    /**
     * Get precision
     * @return Precision
     */
    virtual const double GetPrecision() const = 0;

    /**
     * Set precision
     * @param[in] precision precision
     * @return ER_OK on success
     */
    virtual QStatus SetPrecision(const double precision) = 0;

    /**
     * Get the minimum update time
     * @return The minimum update time
     */
    virtual const uint16_t GetUpdateMinTime() const = 0;

    /**
     * Set the minimum update time
     * @param[in] updateMinTime the minimum update time
     * @return ER_OK on success
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTTEMPERATUREINTFCONTROLLEE_H_ */