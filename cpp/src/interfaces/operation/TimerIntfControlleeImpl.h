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

#ifndef TIMERINTFCONTROLLEEIMPL_H_
#define TIMERINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/operation/TimerIntfControllee.h>

namespace ajn {
namespace services {

class TimerIntfControlleeListener;
class HaeBusObject;

/**
 * Timer Interface Controllee implementation class
 */
class TimerIntfControlleeImpl : public InterfaceControllee, public TimerIntfControllee {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of TimerIntfControlleeImpl
     */
    TimerIntfControlleeImpl(BusAttachment& busAttachment, TimerIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of TimerIntfControlleeImpl
     */
    virtual ~TimerIntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
     virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    virtual const int32_t GetReferenceTimer() const {return m_referenceTimer; }

    virtual QStatus SetReferenceTimer(const int32_t time);

    virtual const int32_t GetTargetTimeToStart() const { return m_targetTimeToStart; }

    virtual const int32_t GetTargetTimeToStop() const { return m_targetTimeToStop; }

    virtual const int32_t GetEstimatedTimeToEnd() const { return (m_targetTimeToStop - m_referenceTimer); }

    virtual QStatus SetEstimatedTimeToEnd(const int32_t time);

    virtual const int32_t GetRunningTime() const { return (m_referenceTimer - m_targetTimeToStart); }

    virtual QStatus SetRunningTime(const int32_t time);

    virtual const int32_t GetTargetDuration() const { return (m_targetTimeToStop - m_targetTimeToStart); }

    virtual QStatus SetTargetDuration(const int32_t time);

    void OnSetTargetTimeToStart(const InterfaceDescription::Member* member, Message& msg);
    void OnSetTargetTimeToStop(const InterfaceDescription::Member* member, Message& msg);
  private:
    TimerIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    TimerIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    int32_t m_referenceTimer;
    int32_t m_targetTimeToStart;
    int32_t m_targetTimeToStop;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLEEIMPL_H_ */
