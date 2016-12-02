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

#ifndef TESTTIMERLISTENER_H_
#define TESTTIMERLISTENER_H_

#include <alljoyn/cdm/interfaces/operation/TimerIntfControlleeListener.h>
using namespace ajn;
using namespace services;
class TestTimerListener : public TimerIntfControlleeListener
{
  private:
    void* m_testControllee;
  public:
    TestTimerListener(void* controllee);

    virtual QStatus GetReferenceTimer(int32_t& time) ;

    virtual QStatus GetTargetTimeToStart(int32_t& time) ;

    virtual QStatus GetTargetTimeToStop(int32_t& time) ;

    virtual QStatus GetEstimatedTimeToEnd(int32_t& time);

    virtual QStatus GetRunningTime(int32_t& time) ;

    virtual QStatus GetTargetDuration(int32_t& time);

    virtual QStatus OnSetTargetTimeToStart(int32_t time, ErrorCode& errorCode) ;

    virtual QStatus OnSetTargetTimeToStop(int32_t time, ErrorCode& errorCode) ;
};

#endif /* TESTTIMERLISTENER_H_ */