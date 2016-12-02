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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLER_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel Interface Controller class
 */
class TargetTemperatureLevelIntfController : public TargetTemperatureLevelInterface {
  public:
    /**
     * Constructor of TargetTemperatureLevelIntfController
     */
    TargetTemperatureLevelIntfController() {}

    /**
     * Destructor of TargetTemperatureLevelIntfController
     */
    virtual ~TargetTemperatureLevelIntfController() {}

    /**
     * Get current target temperature level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetLevel(void* context = NULL) = 0;

    /**
     * Set Target TemperatureLevel
     * @param[in] TargetTemperatureLevel target temperature level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(const uint8_t TargetTemperatureLevel, void* context = NULL) = 0;

    /**
     * Get the maximum value of target temperature level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxLevel(void* context = NULL) = 0;

    /**
     * Get the selectable temperature levels
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSelectableTemperatureLevels(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLER_H_ */