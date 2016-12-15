/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef TIMERMODEL_H_
#define TIMERMODEL_H_

#include <interfaces/controllee/operation/TimerIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class TimerModel : public virtual TimerIntfControlleeModel {
  public:
    TimerModel(const std::string& busPath);

    /**
     * Get ReferenceTimer
     * @return current reference timer
     */
    QStatus GetReferenceTimer(int32_t& out) const override;

    /**
     * Get TargetTimeToStart
     * @return current target time to start
     */
    QStatus GetTargetTimeToStart(int32_t& out) const override;

    /**
     * Get TargetTimeToStop
     * @return current target time to stop
     */
    QStatus GetTargetTimeToStop(int32_t& out) const override;

    /**
     * Get EstimatedTimeToEnd
     * @return current estimated time to end
     */
    QStatus GetEstimatedTimeToEnd(int32_t& out) const override;

    /**
     * Get RunningTime
     * @return current running time
     */
    QStatus GetRunningTime(int32_t& out) const override;

    /**
     * Get TargetDuration
     * @return current target duration
     */
    QStatus GetTargetDuration(int32_t& out) const override;

    /**
     * Handler for method SetTargetTimeToStart
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus SetTargetTimeToStart(int32_t arg_targetTimeToStart, ErrorCode& error, CdmControllee& controllee) override;
    /**
     * Handler for method SetTargetTimeToStop
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus SetTargetTimeToStop(int32_t arg_targetTimeToStop, ErrorCode& error, CdmControllee& controllee) override;

  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* TIMERMODEL_H_ */