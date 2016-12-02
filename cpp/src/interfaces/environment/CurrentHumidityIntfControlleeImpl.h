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

#ifndef CURRENTHUMIDITYINTFCONTROLLEEIMPL_H_
#define CURRENTHUMIDITYINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControllee.h>

namespace ajn {
namespace services {

class CurrentHumidityIntfControlleeListener;
class CdmBusObject;

/**
 * CurrentHumidity interface controllee implementation class
 */
class CurrentHumidityIntfControlleeImpl : public InterfaceControllee, public CurrentHumidityIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of CurrentHumidityIntfControlleeImpl
     */
    CurrentHumidityIntfControlleeImpl(BusAttachment& busAttachment, CurrentHumidityIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of CurrentHumidityIntfControlleeImpl
     */
    virtual ~CurrentHumidityIntfControlleeImpl();

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
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Set current humidity
     * @param[in] value current humidity
     * @return status
     */
    virtual QStatus SetCurrentValue(const uint8_t value);

    /**
     * Get current humidity
     * @return Current humidity
     */
    virtual const uint8_t GetCurrentValue() const { return m_currentValue; }

    /**
     * Set MaxValue
     * @param[in] value max humidity
     * @return status
     */
    virtual QStatus SetMaxValue(const uint8_t value);

    /**
     * Get MaxValue
     * @return MaxValue
     */
    virtual const uint8_t GetMaxValue() const { return m_maxValue; }

  private:
    CurrentHumidityIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    CurrentHumidityIntfControlleeListener& m_interfaceListener;
    uint8_t m_currentValue;                       // read-only, EmitsChangedSignal
    uint8_t m_maxValue;                          // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLEEIMPL_H_ */