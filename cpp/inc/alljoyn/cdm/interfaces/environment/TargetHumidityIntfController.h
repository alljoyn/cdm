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

#ifndef TARGETHUMIDITYINTFCONTROLLER_H_
#define TARGETHUMIDITYINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity Interface Controller class
 */
class TargetHumidityIntfController : public TargetHumidityInterface {
  public:
    /**
     * Constructor of TargetHumidityIntfController
     */
    TargetHumidityIntfController() {}

    /**
     * Destructor of TargetHumidityIntfController
     */
    virtual ~TargetHumidityIntfController() {}

    /**
     * Get current target humidity
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetValue(void* context = NULL) = 0;

    /**
     * Set Target Humidity
     * @param[in] TargetHumidity target humidity
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const uint8_t TargetHumidity, void* context = NULL) = 0;

    /**
     * Get the minimum value of target humidity
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMinValue(void* context = NULL) = 0;

    /**
     * Get the maximum value of target humidity
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxValue(void* context = NULL) = 0;

    /**
     * Get the step value of target humidity
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetStepValue(void* context = NULL) = 0;

    /**
     * Get the selectable humidity levels
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSelectableHumidityLevels(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLER_H_ */