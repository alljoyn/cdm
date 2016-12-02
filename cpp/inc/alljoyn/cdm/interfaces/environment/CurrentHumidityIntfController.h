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

#ifndef CURRENTHUMIDITYINTFCONTROLLER_H_
#define CURRENTHUMIDITYINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity Interface Controller class
 */
class CurrentHumidityIntfController : public CurrentHumidityInterface {
  public:
    /**
     * Constructor of CurrentHumidityIntfController
     */
    CurrentHumidityIntfController() {}

    /**
     * Destructor of CurrentHumidityIntfController
     */
    virtual ~CurrentHumidityIntfController() {}

    /**
     * Get CurrentValue
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentValue(void* context = NULL) = 0;

    /**
     * Get MaxValue
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxValue(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLER_H_ */