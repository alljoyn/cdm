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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLER_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controller class
 */
class CurrentAirQualityLevelIntfController : public CurrentAirQualityLevelInterface {
  public:
    /**
     * Constructor of CurrentAirQualityLevelIntfController
     */
    CurrentAirQualityLevelIntfController() {}

    /**
     * Destructor of CurrentAirQualityLevelIntfController
     */
    virtual ~CurrentAirQualityLevelIntfController() {}

    /**
     * Get ContaminantType
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetContaminantType(void* context = NULL) = 0;

    /**
     * Get CurrentLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentLevel(void* context = NULL) = 0;

    /**
     * Get the maximum level of air quality
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxLevel(void* context = NULL) = 0;

 };

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLER_H_ */