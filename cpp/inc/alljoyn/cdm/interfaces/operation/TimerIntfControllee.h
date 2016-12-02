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

#ifndef TIMERINTFCONTROLLEE_H_
#define TIMERINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/TimerInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Interface Controllee class
 */
class TimerIntfControllee : public TimerInterface {
  public:
    /**
     * Constructor of TimerIntfControllee
     */
    TimerIntfControllee() {}

    /**
     * Destructor of TimerIntfControllee
     */
    virtual ~TimerIntfControllee() {}

    /**
     * Get ReferenceTimer
     * @return The current reference timer value
     */
    virtual const int32_t GetReferenceTimer() const = 0;

    /**
     * Set ReferenceTimer
     * @param[in] time reference timer value
     * @return ER_OK on success
     */
    virtual QStatus SetReferenceTimer(const int32_t time) = 0;

    /**
     * Get TargetTimeToStart
     * @return Time to the start
     */
    virtual const int32_t GetTargetTimeToStart() const = 0;

     /**
     * Set TargetTimeToStart
     * @param[in] time target time to start
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStart(const int32_t time) = 0;

    /**
     * Get TargetTimeToStop
     * @return Time to the stop
     */
    virtual const int32_t GetTargetTimeToStop() const = 0;

     /**
     * Set TargetTimeToStop
     * @param[in] time target time to stop
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStop(const int32_t time) = 0;

    /**
     * Get EstimatedTimeToEnd
     * @return estimated time to the end
     */
    virtual const int32_t GetEstimatedTimeToEnd() const = 0;

    /**
     * Set EstimatedTimeToEnd
     * @param[in] time estimated time to the end
     * @return ER_OK on success
     */
    virtual QStatus SetEstimatedTimeToEnd(const int32_t time) = 0;

    /**
     * Get RunningTime
     * @return running time
     */
    virtual const int32_t GetRunningTime() const = 0;

    /**
     * Set RunningTime
     * @param[in] time running time
     * @return ER_OK on success
     */
    virtual QStatus SetRunningTime(const int32_t time) = 0;

    /**
     * Get TargetDuration
     * @return target duration
     */
    virtual const int32_t GetTargetDuration() const = 0;

    /**
     * Set TargetDuration
     * @param[in] time target duration
     * @return ER_OK on success
     */
    virtual QStatus SetTargetDuration(const int32_t time) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLEE_H_ */