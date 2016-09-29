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
     * Get ReferenceTimer property
     * (Time counter to be used as reference.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetReferenceTimer(void* context = NULL) = 0;

    /**
     * Get TargetTimeToStart property
     * (Time when the appliance is expected to start its operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStart(void* context = NULL) = 0;

    /**
     * Get TargetTimeToStop property
     * (Time when the appliance is expected to stop its operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStop(void* context = NULL) = 0;

    /**
     * Get EstimatedTimeToEnd property
     * (Time to the end of appliance operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetEstimatedTimeToEnd(void* context = NULL) = 0;

    /**
     * Get RunningTime property
     * (Time of current operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetRunningTime(void* context = NULL) = 0;

    /**
     * Get TargetDuration property
     * (Time representing the target duration of the operation as per user selection.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetDuration(void* context = NULL) = 0;

    /**
     * Call SetTargetTimeToStart method
     * @param[in] targetTimeToStart Time to be set.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStart(const int32_t targetTimeToStart, void* context = NULL) = 0;

    /**
     * Call SetTargetTimeToStop method
     * @param[in] targetTimeToStop Time to be set.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStop(const int32_t targetTimeToStop, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLER_H_ */
