/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef TIMERINTFCONTROLLEEIMPL_H_
#define TIMERINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllee.h>

namespace ajn {
namespace services {

class TimerIntfControlleeListener;
class CdmBusObject;

/**
 * Timer Interface Controllee implementation class
 */
class TimerIntfControlleeImpl : public InterfaceControllee, public TimerIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of TimerIntfControlleeImpl
     */
    TimerIntfControlleeImpl(BusAttachment& busAttachment, TimerIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

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
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

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

    /**
     * Get ReferenceTimer
     * @return reference timer value
     */
    virtual const int32_t GetReferenceTimer() const {return m_referenceTimer; }

    /**
     * Set ReferenceTimer
     * @param[in] time
     * @return status
     */
    virtual QStatus SetReferenceTimer(const int32_t time);

    /**
     * Get TargetTimeToStart
     * @return target time to start
     */
    virtual const int32_t GetTargetTimeToStart() const { return m_targetTimeToStart; }

    /**
     * Set TargetTimeToStart
     * @param[in] time
     * @return status
     */
    virtual QStatus SetTargetTimeToStart(const int32_t time);

    /**
     * Get TargetTimeToStop
     * @return target time to stop
     */
    virtual const int32_t GetTargetTimeToStop() const { return m_targetTimeToStop; }

     /**
     * Set TargetTimeToStop
     * @param[in] time
     * @return status
     */
    virtual QStatus SetTargetTimeToStop(const int32_t time);

    /**
     * Get EstimatedTimeToEnd
     * @return estimated time to end
     */
    virtual const int32_t GetEstimatedTimeToEnd() const { return m_estimatedTimeToEnd; }

    /**
     * Set EstimatedTimeToEnd
     * @param[in] time
     * @return status
     */
    virtual QStatus SetEstimatedTimeToEnd(const int32_t time);

    /**
     * Get RunningTime
     * @return running time
     */
    virtual const int32_t GetRunningTime() const { return m_runningTime; }

    /**
     * Set RunningTime
     * @param[in] time
     * @return status
     */
    virtual QStatus SetRunningTime(const int32_t time);

    /**
     * Get TargetDuration
     * @return target duration
     */
    virtual const int32_t GetTargetDuration() const { return m_targetDuration; }

    /**
     * Set TargetDuration
     * @param[in] time
     * @return status
     */
    virtual QStatus SetTargetDuration(const int32_t time);

    /**
     * Handler of SetTargetTimeToStart method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSetTargetTimeToStart(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Handler of SetTargetTimeToStop method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSetTargetTimeToStop(const InterfaceDescription::Member* member, Message& msg);

  private:
    TimerIntfControlleeImpl();
    void UpdateProperties();

    BusAttachment& m_busAttachment;
    TimerIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    int32_t m_referenceTimer;
    int32_t m_targetTimeToStart;
    int32_t m_targetTimeToStop;
    int32_t m_estimatedTimeToEnd;
    int32_t m_runningTime;
    int32_t m_targetDuration;

};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLEEIMPL_H_ */