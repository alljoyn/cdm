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

// This file is automatically generated. Do not edit it.

#ifndef TIMERINTFCONTROLLERLISTENER_H_
#define TIMERINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/operation/TimerInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Interface Controller Listener class
 */
class TimerIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TimerIntfControllerListener
     */
    virtual ~TimerIntfControllerListener() {}

    /**
     * Callback handler for GetReferenceTimer completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of ReferenceTimer
     *                  (Time counter to be used as reference.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) {}

    /**
     * Handler for ReferenceTimer property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of ReferenceTimer
     *                  (Time counter to be used as reference.)
     */
    virtual void OnReferenceTimerChanged(const qcc::String& objectPath, const int32_t value) {}

    /**
     * Callback handler for GetTargetTimeToStart completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetTimeToStart
     *                  (Time when the appliance is expected to start its operation.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) {}

    /**
     * Handler for TargetTimeToStart property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetTimeToStart
     *                  (Time when the appliance is expected to start its operation.)
     */
    virtual void OnTargetTimeToStartChanged(const qcc::String& objectPath, const int32_t value) {}

    /**
     * Callback handler for GetTargetTimeToStop completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetTimeToStop
     *                  (Time when the appliance is expected to stop its operation.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) {}

    /**
     * Handler for TargetTimeToStop property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetTimeToStop
     *                  (Time when the appliance is expected to stop its operation.)
     */
    virtual void OnTargetTimeToStopChanged(const qcc::String& objectPath, const int32_t value) {}

    /**
     * Callback handler for GetEstimatedTimeToEnd completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of EstimatedTimeToEnd
     *                  (Time to the end of appliance operation.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) {}

    /**
     * Handler for EstimatedTimeToEnd property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of EstimatedTimeToEnd
     *                  (Time to the end of appliance operation.)
     */
    virtual void OnEstimatedTimeToEndChanged(const qcc::String& objectPath, const int32_t value) {}

    /**
     * Callback handler for GetRunningTime completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of RunningTime
     *                  (Time of current operation.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) {}

    /**
     * Handler for RunningTime property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of RunningTime
     *                  (Time of current operation.)
     */
    virtual void OnRunningTimeChanged(const qcc::String& objectPath, const int32_t value) {}

    /**
     * Callback handler for GetTargetDuration completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetDuration
     *                  (Time representing the target duration of the operation as per user selection.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) {}

    /**
     * Handler for TargetDuration property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetDuration
     *                  (Time representing the target duration of the operation as per user selection.)
     */
    virtual void OnTargetDurationChanged(const qcc::String& objectPath, const int32_t value) {}

    /**
     * Callback handler for SetTargetTimeToStart completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseSetTargetTimeToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for SetTargetTimeToStop completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseSetTargetTimeToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLERLISTENER_H_ */