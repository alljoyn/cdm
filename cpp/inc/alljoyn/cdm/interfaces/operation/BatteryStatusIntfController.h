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

#ifndef BATTERYSTATUSINTFCONTROLLER_H_
#define BATTERYSTATUSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusInterface.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controller class
 */
class BatteryStatusIntfController : public BatteryStatusInterface {
  public:
    /**
     * Constructor of BatteryStatusIntfController
     */
    BatteryStatusIntfController() {}

    /**
     * Destructor of BatteryStatusIntfController
     */
    virtual ~BatteryStatusIntfController() {}

    /**
     * Get current value of bettery status
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentValue(void* context = NULL) = 0;

    /**
     * Get if battery is being charged
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsCharging(void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLER_H_ */