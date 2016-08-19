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

#ifndef TIMERINTFCONTROLLERLISTENER_H_
#define TIMERINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * Timer Interface Controller Listener class
 */
class TimerIntfControllerListener : public InterfaceControllerListener
{
  public:
    virtual ~TimerIntfControllerListener() {}

    /**
     * Callback handler for getting ReferenceTimer property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] time reference timer value
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, int32_t& time, void* context) {}
    /**
     * Callback handler for getting TargetTimeToStart property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] time target time to start
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, int32_t& time, void* context) {}
    /**
     * Callback handler for getting TargetTimeToStop property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] timt target time to stop
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, int32_t& time, void* context) {}
    /**
     * Callback handler for getting EstimatedTimeToEnd property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] time estimated time to end
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, int32_t& time, void* context) {}
    /**
     * Callback handler for getting RunningTime property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] time running time
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, int32_t& time, void* context) {}
    /**
     * Callback handler for getting TargetDuration property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] time target duration
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, int32_t& time, void* context) {}

    /**
     * Handler for ReferenceTimer property changed
     * @param[in] objectPath the object path
     * @param[in] time reference timer value
     */
    virtual void OnReferenceTimerPropertyChanged(const qcc::String& objectPath, int32_t time) {}
    /**
     * Handler for TargetTimeToStart property changed
     * @param[in] objectPath the object path
     * @param[in] time target time to start
     */
    virtual void OnTargetTimeToStartPropertyChanged(const qcc::String& objectPath, int32_t time) {}
    /**
     * Handler for TargetTimeToStop property changed
     * @param[in] objectPath the object path
     * @param[in] time target time to stop
     */
    virtual void OnTargetTimeToStopPropertyChanged(const qcc::String& objectPath, int32_t time) {}
    /**
     * Handler for EstimatedTimeToEnd property changed
     * @param[in] objectPath the object path
     * @param[in] time estimated time to end
     */
    virtual void OnEstimatedTimeToEndPropertyChanged(const qcc::String& objectPath, int32_t time) {}
    /**
     * Handler for RunningTime property changed
     * @param[in] objectPath the object path
     * @param[in] time running time
     */
    virtual void OnRunningTimePropertyChanged(const qcc::String& objectPath, int32_t time) {}
    /**
     * Handler for TargetDuration property changed
     * @param[in] objectPath the object path
     * @param[in] time target duration
     */
    virtual void OnTargetDurationPropertyChanged(const qcc::String& objectPath, int32_t time) {}

    /**
     * Callback handler for SetTargetTimerToStart method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseSetTargetTimerToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {};
    /**
     * Callback handler for SetTargetTimerToStop method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseSetTargetTimerToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {};
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLERLISTENER_H_ */
