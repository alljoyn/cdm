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

#ifndef TIMERINTFCONTROLLEELISTENER_H_
#define TIMERINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/TimerInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Interface Controllee Listener class
 */
class TimerIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of TimerIntfControlleeListener
     */
    virtual ~TimerIntfControlleeListener() {}

    /**
     * Handler for getting ReferenceTimer
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] time reference timer value
     * @return ER_OK on success
     */
    virtual QStatus GetReferenceTimer(int32_t& time) = 0;

    /**
     * Handler for getting TargetTimeToStart
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] time target time start
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStart(int32_t& time) = 0;

    /**
     * Handler for getting TargetTimeToStop
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] time target time stop
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStop(int32_t& time) = 0;

    /**
     * Handler for getting EstimatedTimeToEnd
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] time estimated time to end
     * @return ER_OK on success
     */
    virtual QStatus GetEstimatedTimeToEnd(int32_t& time) = 0;

    /**
     * Handler for getting RunningTime
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] time running time
     * @return ER_OK on success
     */
    virtual QStatus GetRunningTime(int32_t& time) = 0;

    /**
     * Handler for getting TargetDuration
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] time target duration
     * @return ER_OK on success
     */
    virtual QStatus GetTargetDuration(int32_t& time) = 0;

    /**
     * Handler for setting TargetTimeToStart
     * @param[in] time target time to start
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetTimeToStart(int32_t time, ErrorCode& errorCode) = 0;

    /**
     * Handler for setting TargetTimeToStop
     * @param[in] time target time to stop
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetTimeToStop(int32_t time, ErrorCode& errorCode) = 0;

};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLEELISTENER_H_ */