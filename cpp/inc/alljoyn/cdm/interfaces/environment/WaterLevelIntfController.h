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

#ifndef WATERLEVELINTFCONTROLLER_H_
#define WATERLEVELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelInterface.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface Controller class
 */
class WaterLevelIntfController : public WaterLevelInterface {
  public:
    /**
     * Constructor of WaterLevelIntfController
     */
    WaterLevelIntfController() {}

    /**
     * Destructor of WaterLevelIntfController
     */
    virtual ~WaterLevelIntfController() {}

    /**
     * Get currentLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentLevel(void* context = NULL) = 0;

    /**
     * Get supplySource
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupplySource(void* context = NULL) = 0;

    /**
     * Get maxLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxLevel(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLER_H_ */