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

#ifndef CURRENTAIRQUALITYINTFCONTROLLER_H_
#define CURRENTAIRQUALITYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controller class
 */
class CurrentAirQualityIntfController : public CurrentAirQualityInterface {
  public:
    /**
     * Constructor of CurrentAirQualityIntfController
     */
    CurrentAirQualityIntfController() {}

    /**
     * Destructor of CurrentAirQualityIntfController
     */
    virtual ~CurrentAirQualityIntfController() {}

    /**
     * Get ContaminantType
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetContaminantType(void* context = NULL) = 0;

    /**
     * Get CurrentValue
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentValue(void* context = NULL) = 0;

    /**
     * Get the maximum value of air quality
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxValue(void* context = NULL) = 0;

    /**
     * Get the minimum value of air quality
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMinValue(void* context = NULL) = 0;

    /**
     * Get Precision
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPrecision(void* context = NULL) = 0;

    /**
     * Get UpdateMinTime
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetUpdateMinTime(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLER_H_ */