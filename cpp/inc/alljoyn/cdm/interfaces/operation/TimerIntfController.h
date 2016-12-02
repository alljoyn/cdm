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

#ifndef TIMERINTFCONTROLLER_H_
#define TIMERINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/TimerInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Interface Controller class
 */
class TimerIntfController : public TimerInterface {
  public:
    /**
     * Constructor of TimerIntfController
     */
    TimerIntfController() {}

    /**
     * Destructor of TimerIntfController
     */
    virtual ~TimerIntfController() {}

    /**
     * Get ReferenceTimer
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetReferenceTimer(void* context = NULL) = 0;

    /**
     * Get TargetTimeToStart
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStart(void* context = NULL) = 0;

    /**
     * Get TargetTimeToStop
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStop(void* context = NULL) = 0;

    /**
     * Get EstimatedTimeToEnd
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetEstimatedTimeToEnd(void* context = NULL) = 0;

    /**
     * Get RunningTime
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetRunningTime(void* context = NULL) = 0;

    /**
     * Get TargetDuration
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetDuration(void* context = NULL) = 0;

    /**
     * Set target time to start
     * @param[in] time time to start
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStart(int32_t time, void* context = NULL) = 0;

    /**
     * Set target time to stop
     * @param[in] time time to stop
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStop(int32_t time, void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLER_H_ */