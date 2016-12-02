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

#ifndef CURRENTAIRQUALITYINTFCONTROLLEEIMPL_H_
#define CURRENTAIRQUALITYINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllee.h>

namespace ajn {
namespace services {

class CurrentAirQualityIntfControlleeListener;
class CdmBusObject;

/**
 * CurrentAirQuality Interface Controllee implementation class
 */
class CurrentAirQualityIntfControlleeImpl : public InterfaceControllee, public CurrentAirQualityIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of CurrentAirQualityIntfControlleeImpl
     */
    CurrentAirQualityIntfControlleeImpl(BusAttachment& busAttachment, CurrentAirQualityIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of CurrentAirQualityIntfControlleeImpl
     */
    virtual ~CurrentAirQualityIntfControlleeImpl();

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
     * Set contaminant type
     * @param[in] type contamiant type
     * @return status
     */
    virtual QStatus SetContaminantType(const uint8_t type);

    /**
     * Get contaminant type
     * @return contaminant type
     */
    virtual const uint8_t GetContaminantType() const { return m_contaminantType; }

    /**
     * Set current air quality
     * @param[in] value current air quality
     * @return status
     */
    virtual QStatus SetCurrentValue(const double value);

    /**
     * Get air quality
     * @return air quality
     */
    virtual const double GetCurrentValue() const { return m_currentValue; }

    /**
     * Set maximum air quality
     * @param[in] value maximum air quality
     * @return status
     */
    virtual QStatus SetMaxValue(const double value);

    /**
     * Get maximum air quality
     * @return maximum air quality
     */
    virtual const double GetMaxValue() const { return m_maxValue; }

    /**
     * Set minimum air quality
     * @param[in] value minimum air quality
     * @return status
     */
    virtual QStatus SetMinValue(const double value);

    /**
     * Get minimum air quality
     * @return minimum air quality
     */
    virtual const double GetMinValue() const { return m_minValue; }

    /**
     * Set precision
     * @param[in] precision precision
     * @return status
     */
    virtual QStatus SetPrecision(const double precision);

    /**
     * Get precision
     * @return Precision
     */
    virtual const double GetPrecision() const { return m_precision; }

    /**
     * Set the minimum update time
     * @param[in] updateMinTime the minimum update time
     * @return status
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime);

    /**
     * Get the minimum update time
     * @return The minimum update time
     */
    virtual const uint16_t GetUpdateMinTime() const { return m_updateMinTime; }


  private:
    CurrentAirQualityIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    CurrentAirQualityIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint8_t m_contaminantType;          // read-only, EmitsChangedSignal
    double m_currentValue;              // read-only, EmitsChangedSignal
    double m_maxValue;                  // read-only, EmitsChangedSignal
    double m_minValue;                  // read-only, EmitsChangedSignal
    double m_precision;                 // read-only, EmitsChangedSignal
    uint16_t m_updateMinTime;           // read-only, EmitsChangedSignal
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLEEIMPL_H_ */