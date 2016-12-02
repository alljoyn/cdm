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

#ifndef HEATINGZONEINTFCONTROLLEEIMPL_H_
#define HEATINGZONEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllee.h>

namespace ajn {
namespace services {

class HeatingZoneIntfControlleeListener;
class CdmBusObject;

/**
 * HeatingZone Interface Controllee implementation class
 */
class HeatingZoneIntfControlleeImpl : public InterfaceControllee, public HeatingZoneIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of HeatingZoneIntfControlleeImpl
     */
    HeatingZoneIntfControlleeImpl(BusAttachment& busAttachment, HeatingZoneIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of HeatingZoneIntfControlleeImpl
     */
    virtual ~HeatingZoneIntfControlleeImpl();

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
     * Get number of heating zones
     * @return NumberOfHeatingZones
     */
    virtual const uint8_t GetNumberOfHeatingZones() const { return m_numberOfHeatingLevels; }

    /**
     * Set NumberOfHeatingZones
     * @param[in] numberOfZones number of heating zones
     * @return ER_OK on success
     */
    virtual QStatus SetNumberOfHeatingZones(const uint8_t numberOfZones);

    /**
     * Get MaxHeatingLevels
     * @return the list of maximum heating levels
     */
    virtual const std::vector<uint8_t>& GetMaxHeatingLevels() const { return m_maxHeatingLevels; }

    /**
     * Set MaxHeatingLevels
     * @param[in] maxHeatingLevels maxHeatingLevels
     * @return ER_OK on success
     */
    virtual QStatus SetMaxHeatingLevels(const std::vector<uint8_t>& maxHeatingLevels);

    /**
     * Get HeatingLevels
     * @return the list of heating levels
     */
    virtual const std::vector<uint8_t>& GetHeatingLevels() const { return m_heatingLevels; }

    /**
     * Set HeatingLevels
     * @param[in] heatingLevels heatingLevels
     * @return ER_OK on success
     */
    virtual QStatus SetHeatingLevels(const std::vector<uint8_t>& heatingLevels);

  private:
    HeatingZoneIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    HeatingZoneIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    std::vector<uint8_t> m_maxHeatingLevels;
    std::vector<uint8_t> m_heatingLevels;
    uint8_t m_numberOfHeatingLevels;
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLEEIMPL_H_ */