/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
