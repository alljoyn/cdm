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

#ifndef TIMERINTFCONTROLLEELISTENER_H_
#define TIMERINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/TimerInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Model Interface class for the Controllee
 */
class TimerIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of TimerIntfControlleeModel
     */
    virtual ~TimerIntfControlleeModel() {}

    /**
     * Get ReferenceTimer
     * @return current reference timer
     */
    virtual QStatus GetReferenceTimer(int32_t& out) const = 0;
    /**
     * Get TargetTimeToStart
     * @return current target time to start
     */
    virtual QStatus GetTargetTimeToStart(int32_t& out) const = 0;
    /**
     * Get TargetTimeToStop
     * @return current target time to stop
     */
    virtual QStatus GetTargetTimeToStop(int32_t& out) const = 0;
    /**
     * Get EstimatedTimeToEnd
     * @return current estimated time to end
     */
    virtual QStatus GetEstimatedTimeToEnd(int32_t& out) const = 0;
    /**
     * Get RunningTime
     * @return current running time
     */
    virtual QStatus GetRunningTime(int32_t& out) const = 0;
    /**
     * Get TargetDuration
     * @return current target duration
     */
    virtual QStatus GetTargetDuration(int32_t& out) const = 0;

    /**
     * Handler for method SetTargetTimeToStart
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStart(int32_t arg_targetTimeToStart, ErrorCode& error, CdmSideEffects& sideEffects) = 0;
    /**
     * Handler for method SetTargetTimeToStop
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStop(int32_t arg_targetTimeToStop, ErrorCode& error, CdmSideEffects& sideEffects) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLEELISTENER_H_ */
