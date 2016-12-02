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

#ifndef CURRENTTEMPERATUREINTFCONTROLLER_H_
#define CURRENTTEMPERATUREINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentTemperature Interface Controller class
 */
class CurrentTemperatureIntfController : public CurrentTemperatureInterface {
  public:
    /**
     * Constructor of CurrentTemperatureIntfController
     */
    CurrentTemperatureIntfController() {}

    /**
     * Destructor of CurrentTemperatureIntfController
     */
    virtual ~CurrentTemperatureIntfController() {}

    /**
     * Get CurrentValue
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentValue(void* context = NULL) = 0;

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

#endif /* CURRENTTEMPERATUREINTFCONTROLLER_H_ */