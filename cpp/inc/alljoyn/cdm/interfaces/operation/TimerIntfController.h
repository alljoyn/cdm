/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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