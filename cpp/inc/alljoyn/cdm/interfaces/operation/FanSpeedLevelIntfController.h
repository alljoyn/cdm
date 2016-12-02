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

#ifndef FANSPEEDLEVELINTFCONTROLLER_H_
#define FANSPEEDLEVELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controller class
 */
class FanSpeedLevelIntfController : public FanSpeedLevelInterface {
  public:
    /**
     * Constructor of FanSpeedLevelIntfController
     */
    FanSpeedLevelIntfController() {}

    /**
     * Destructor of FanSpeedLevelIntfController
     */
    virtual ~FanSpeedLevelIntfController() {}

    /**
     * Get FanSpeedLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetFanSpeedLevel(void* context = NULL) = 0;

    /**
     * Set FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetFanSpeedLevel(const uint8_t value, void* context = NULL) = 0;

    /**
     * Get MaxFanSpeedLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxFanSpeedLevel(void* context = NULL) = 0;

    /**
     * Get AutoMode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAutoMode(void* context = NULL) = 0;

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const uint8_t value, void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLER_H_ */