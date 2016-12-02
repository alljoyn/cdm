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

#ifndef CURRENTHUMIDITYINTFCONTROLLEE_H_
#define CURRENTHUMIDITYINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity Interface Controllee class
 */
class CurrentHumidityIntfControllee : public CurrentHumidityInterface {
  public:
    /**
     * Constructor of CurrentHumidityIntfControllee
     */
    CurrentHumidityIntfControllee() {}

    /**
     * Destructor of CurrentHumidityIntfControllee
     */
    virtual ~CurrentHumidityIntfControllee() {}

    /**
     * Get current humidity
     * @return Current humidity
     */
    virtual const uint8_t GetCurrentValue() const = 0;

    /**
     * Set current humidity
     * @param[in] value current humidity
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentValue(const uint8_t value) = 0;

    /**
     * Get MaxValue
     * @return MaxValue
     */
    virtual const uint8_t GetMaxValue() const = 0;

    /**
     * Set MaxValue
     * @param[in] value max humidity
     * @return ER_OK on success
     */
    virtual QStatus SetMaxValue(const uint8_t value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLEE_H_ */