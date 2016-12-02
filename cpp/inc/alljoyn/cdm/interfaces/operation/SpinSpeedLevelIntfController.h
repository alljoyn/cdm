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

#ifndef SPINSPEEDLEVELINTFCONTROLLER_H_
#define SPINSPEEDLEVELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * SpinSpeedLevel Interface Controller class
 */
class SpinSpeedLevelIntfController : public SpinSpeedLevelInterface {
  public:
    /**
     * Constructor of SpinSpeedLevelIntfController
     */
    SpinSpeedLevelIntfController() {}

    /**
     * Destructor of SpinSpeedLevelIntfController
     */
    virtual ~SpinSpeedLevelIntfController() {}

    /**
     * Get MaxLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxLevel(void* context = NULL) = 0;

    /**
     * Get TargetLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetLevel(void* context = NULL) = 0;

    /**
     * Set TargetLevel
     * @param[in] targetLevel targetLevel
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(const uint8_t targetLevel, void* context = NULL) = 0;

    /**
     * Get SelectableLevels
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSelectableLevels(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* SPINSPEEDLEVELINTFCONTROLLER_H_ */