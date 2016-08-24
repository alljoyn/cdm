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

#ifndef TIMERINTFCONTROLLERIMPL_H_
#define TIMERINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfController.h>

namespace ajn {
namespace services {

class TimerIntfControllerListener;
class CdmProxyBusObject;

/**
 * Timer Interface Controller implementation class
 */
class TimerIntfControllerImpl : public InterfaceController, public TimerIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of TimerIntfControllerImpl
     */
    TimerIntfControllerImpl(BusAttachment& busAttachment, TimerIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

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
     * Get ReferenceTimer
     * @param[in] context
     * @return status
     */
    virtual QStatus GetReferenceTimer(void* context );

    /**
     * Get target time to start
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetTimeToStart(void* context );

    /**
     * Get target time to stop
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetTimeToStop(void* context );

    /**
     * Get estimated time to end
     * @param[in] context
     * @return status
     */
    virtual QStatus GetEstimatedTimeToEnd(void* context );

    /**
     * Get running time
     * @param[in] context
     * @return status
     */
    virtual QStatus GetRunningTime(void* context );

    /**
     * Get target duration
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetDuration(void* context );

    /**
     * Set starget time to start
     * @param[in] time
     * @param[in] context
     * @return status
     */
    virtual QStatus SetTargetTimeToStart(int32_t time, void* context );

    /**
     * Set starget time to stop
     * @param[in] time
     * @param[in] context
     * @return status
     */
    virtual QStatus SetTargetTimeToStop(int32_t time, void* context );

  private:
    TimerIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetReferenceTimerCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetTimeToStartCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetTimeToStopCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetEstimatedTimeToEndCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetRunningTimeCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetDurationCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void SetTargetTimeToStartReplyHandler(Message& message, void* context);
    void SetTargetTimeToStopReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    TimerIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLERIMPL_H_ */
