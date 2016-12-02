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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLEEIMPL_H_
#define TEMPERATUREDISPLAYINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllee.h>

namespace ajn {
namespace services {

class TemperatureDisplayIntfControlleeListener;
class CdmBusObject;

/**
 * TemperatureDisplay Interface Controllee implementation class
 */
class TemperatureDisplayIntfControlleeImpl : public InterfaceControllee, public TemperatureDisplayIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of TemperatureDisplayIntfControlleeImpl
     */
    TemperatureDisplayIntfControlleeImpl(BusAttachment& busAttachment, TemperatureDisplayIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TemperatureDisplayIntfControlleeImpl
     */
    virtual ~TemperatureDisplayIntfControlleeImpl();

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
     * Get DisplayTemperatureUnit
     * @return display temperature unit
     */
    virtual const uint8_t GetDisplayTemperatureUnit() { return m_temperatureUnit; }

    /**
     * Set DisplayTemperatureUnit
     * @param[in] temperatureUnit temperature Unit
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t temperatureUnit);

    /**
     * Get SupportedDisplayTemperatureUnits
     * @return list of supported temerature units
     */
    virtual const std::vector<uint8_t>& GetSupportedDisplayTemperatureUnits() { return m_supportedTemperatureUnits; }

    /**
     * Set SupportedDisplayTemperatureUnits
     * @param[in] supportedTemperatureUnits list of supported temperature units
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayTemperatureUnits(const std::vector<uint8_t>& supportedTemperatureUnits);
  private:
    TemperatureDisplayIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    TemperatureDisplayIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint8_t m_temperatureUnit;
    std::vector<uint8_t> m_supportedTemperatureUnits;

};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLEEIMPL_H_ */