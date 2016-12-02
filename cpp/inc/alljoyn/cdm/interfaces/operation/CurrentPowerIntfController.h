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

#ifndef CURRENTPOWERINTFCONTROLLER_H_
#define CURRENTPOWERINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentPower Interface Controller class
 */
class CurrentPowerIntfController : public CurrentPowerInterface {
  public:
    /**
     * Constructor of CurrentPowerIntfController
     */
    CurrentPowerIntfController() {}

    /**
     * Destructor of CurrentPowerIntfController
     */
    virtual ~CurrentPowerIntfController() {}

    /**
     * Get CurrentPower
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentPower(void* context = NULL) = 0;

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

#endif /* CURRENTPOWERINTFCONTROLLER_H_ */