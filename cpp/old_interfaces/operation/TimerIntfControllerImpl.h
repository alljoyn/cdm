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

#ifndef TIMERINTFCONTROLLERIMPL_H_
#define TIMERINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfController.h>

namespace ajn {
namespace services {

class TimerIntfControllerListener;

/**
 * Timer Interface Controller implementation class
 */
class TimerIntfControllerImpl : public InterfaceController, public TimerIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of TimerIntfControllerImpl
     */
    TimerIntfControllerImpl(BusAttachment& busAttachment, TimerIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of TimerIntfControllerImpl
     */
    virtual ~TimerIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get ReferenceTimer property
     * (Time counter to be used as reference.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetReferenceTimer(void* context);

    /**
     * Get TargetTimeToStart property
     * (Time when the appliance is expected to start its operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStart(void* context);

    /**
     * Get TargetTimeToStop property
     * (Time when the appliance is expected to stop its operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetTimeToStop(void* context);

    /**
     * Get EstimatedTimeToEnd property
     * (Time to the end of appliance operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetEstimatedTimeToEnd(void* context);

    /**
     * Get RunningTime property
     * (Time of current operation.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetRunningTime(void* context);

    /**
     * Get TargetDuration property
     * (Time representing the target duration of the operation as per user selection.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetDuration(void* context);

    /**
     * Call SetTargetTimeToStart method
     * @param[in] targetTimeToStart Time to be set.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStart(const int32_t targetTimeToStart, void* context);

    /**
     * Call SetTargetTimeToStop method
     * @param[in] targetTimeToStop Time to be set.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetTimeToStop(const int32_t targetTimeToStop, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetReferenceTimerPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetTimeToStartPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetTimeToStopPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetEstimatedTimeToEndPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetRunningTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetDurationPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetTargetTimeToStartReplyHandler(Message& message, void* context);
    void SetTargetTimeToStopReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    TimerIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLERIMPL_H_ */