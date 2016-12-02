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

#ifndef BATTERYSTATUSINTFCONTROLLEELISTENER_H_
#define BATTERYSTATUSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controllee Listener class
 */
class BatteryStatusIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of BatteryStatusIntfControlleeListener
     */
    virtual ~BatteryStatusIntfControlleeListener() {}

    /**
     * Handler for getting current value of battery status
     * @param[in] value current value
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentValue(uint8_t& value) = 0;

    /**
     * Handler for getting IsCharging property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] isCharging if battery is being charged or not
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsCharging(bool& isCharging) = 0;
};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLEELISTENER_H_ */