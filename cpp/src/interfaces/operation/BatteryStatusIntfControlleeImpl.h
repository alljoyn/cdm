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

#ifndef BATTERYSTATUSINTFCONTROLLEEIMPL_H_
#define BATTERYSTATUSINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllee.h>

namespace ajn {
namespace services {

class BatteryStatusIntfControlleeListener;
class CdmBusObject;

/**
 * BatteryStatus Interface Controllee implementation class
 */
class BatteryStatusIntfControlleeImpl : public InterfaceControllee, public BatteryStatusIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of BatteryStatusIntfControlleeImpl
     */
    BatteryStatusIntfControlleeImpl(BusAttachment& busAttachment, BatteryStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of BatteryStatusIntfControlleeImpl
     */
    virtual ~BatteryStatusIntfControlleeImpl();

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
     * Set current value of battery status
     * @param[in] value
     * @return status
     */
    virtual QStatus SetCurrentValue(const uint8_t value);

    /**
     * Get current value of battery status
     * @return value
     */
    virtual const uint8_t GetCurrentValue() const { return m_currentValue; }

    /**
     * Set if battery is being charged
     * @param[in] isCharging if battery is being charged or not
     * @return ER_OK on success
     */
    virtual QStatus SetIsCharging(const bool isCharging);

    /**
     * Get if battery is being charged
     * @return If battery is being charged or not
     */
    virtual const bool GetIsCharging() const { return m_isCharging; }

  private:
    BatteryStatusIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    BatteryStatusIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint8_t m_currentValue;
    bool m_isCharging;
};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLEEIMPL_H_ */