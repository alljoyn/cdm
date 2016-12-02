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

#ifndef TARGETTEMPERATUREINTFCONTROLLER_H_
#define TARGETTEMPERATUREINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature Interface Controller class
 */
class TargetTemperatureIntfController : public TargetTemperatureInterface {
  public:
    /**
     * Constructor of TargetTemperatureIntfController
     */
    TargetTemperatureIntfController() {}

    /**
     * Destructor of TargetTemperatureIntfController
     */
    virtual ~TargetTemperatureIntfController() {}

    /**
     * Get current target temperature
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetValue(void* context = NULL) = 0;

    /**
     * Set Target Temperature
     * @param[in] TargetTemperature target temperature
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const double TargetTemperature, void* context = NULL) = 0;

    /**
     * Get the minimum value of target temperature
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMinValue(void* context = NULL) = 0;

    /**
     * Get the maximum value of target temperature
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxValue(void* context = NULL) = 0;

    /**
     * Get the step value of target temperature
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetStepValue(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLER_H_ */