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

#ifndef BATTERYSTATUSINTFCONTROLLERLISTENER_H_
#define BATTERYSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controller Listener class
 */
class BatteryStatusIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~BatteryStatusIntfControllerListener() {}

    /**
     * Callback handler for getting CurrentValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] volume volume
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t currentValue, void* context) {}

    /**
     * Callback handler for getting IsCharging property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isCharging if battery is being charged or not
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool isCharging, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] volume volume
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t currentValue) {}

    /**
     * Handler for IsCharging property changed
     * @param[in] objectPath the object path
     * @param[in] isCharging if batter is being charged or not
     */
    virtual void OnIsChargingChanged(const qcc::String& objectPath, const bool isCharging) {}

};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLERLISTENER_H_ */