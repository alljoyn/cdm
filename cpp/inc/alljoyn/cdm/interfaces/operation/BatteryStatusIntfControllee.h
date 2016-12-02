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

#ifndef BATTERYSTATUSINTFCONTROLLEE_H_
#define BATTERYSTATUSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusInterface.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controllee class
 */
class BatteryStatusIntfControllee : public BatteryStatusInterface {
  public:
    /**
     * Constructor of BatteryStatusIntfControllee
     */
    BatteryStatusIntfControllee() {}

    /**
     * Destructor of BatteryStatusIntfControllee
     */
    virtual ~BatteryStatusIntfControllee() {}

    /**
     * Set current value of battery status
     * @param[in] value current value
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentValue(const uint8_t value) = 0;

    /**
     * Get the battery status
     * @return The current battery status
     */
    virtual const uint8_t GetCurrentValue() const = 0;

    /**
     * Set if battery is being charged
     * @param[in] isCharging if battery is being charged or not
     * @return ER_OK on success
     */
    virtual QStatus SetIsCharging(const bool isCharging) = 0;

    /**
     * Get if battery is being charged
     * @return If battery is being charged or not
     */
    virtual const bool GetIsCharging() const = 0;
};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLEE_H_ */