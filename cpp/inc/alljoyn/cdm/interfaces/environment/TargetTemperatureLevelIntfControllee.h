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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLEE_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel Interface Controllee class
 */
class TargetTemperatureLevelIntfControllee : public TargetTemperatureLevelInterface {
  public:

    /**
     * Constructor of TargetTemperatureLevelIntfControllee
     */
    TargetTemperatureLevelIntfControllee() {}

    /**
     * Destructor of TargetTemperatureLevelIntfControllee
     */
    virtual ~TargetTemperatureLevelIntfControllee() {}

    /**
     * Get target temperature level
     * @return Target temperature level
     */
    virtual const uint8_t GetTargetLevel() const = 0;

    /**
     * Set target temperature level
     * @param[in] value the target temperature level
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(const uint8_t value) = 0;

    /**
     * Get the maximum value of target temperature level
     * @return The maximum value of target temperature level
     */
    virtual const uint8_t GetMaxLevel() const = 0;

    /**
     * Set the maximum value of target temperature level
     * @param[in] value the maximum value of target temperature level
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(const uint8_t value) = 0;

    /**
     * Get the selectable temperature level
     * @return The selectable temperature level
     */
    virtual const TargetTemperatureLevelInterface::TemperatureLevels& GetSelectableTemperatureLevels() const = 0;

    /**
     * Set the selectable temperature level
     * @param[in] value the selectable temperature level
     * @return ER_OK on success
     */
    virtual QStatus SetSelectableTemperatureLevels(const TargetTemperatureLevelInterface::TemperatureLevels& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLEE_H_ */