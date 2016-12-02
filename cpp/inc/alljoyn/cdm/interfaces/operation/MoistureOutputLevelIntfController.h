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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel Interface Controller class
 */
class MoistureOutputLevelIntfController : public MoistureOutputLevelInterface {
  public:
    /**
     * Constructor of MoistureOutputLevelIntfController
     */
    MoistureOutputLevelIntfController() {}

    /**
     * Destructor of MoistureOutputLevelIntfController
     */
    virtual ~MoistureOutputLevelIntfController() {}

    /**
     * Get moisture output level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMoistureOutputLevel (void* context = NULL) = 0;

    /**
     * Set moisture output level
     * @param[in] value moisture output level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMoistureOutputLevel (const uint8_t value, void* context = NULL) = 0;

    /**
     * Get the maximum moisture output level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxMoistureOutputLevel (void* context = NULL) = 0;

    /**
     * Get auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAutoMode (void* context = NULL) = 0;

    /**
     * Set auto mode
     * @param[in] autoMOde auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode (const uint8_t autoMode, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLER_H_ */