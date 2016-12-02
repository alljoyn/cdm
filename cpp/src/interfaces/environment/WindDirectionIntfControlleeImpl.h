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

#ifndef WINDDIRECTIONINTFCONTROLLEEIMPL_H_
#define WINDDIRECTIONINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControllee.h>

namespace ajn {
namespace services {

class WindDirectionIntfControlleeListener;
class CdmBusObject;

/**
 * WindDirection interface controllee implementation class
 */
class WindDirectionIntfControlleeImpl : public InterfaceControllee, public WindDirectionIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of WindDirectionIntfControlleeImpl
     */
    WindDirectionIntfControlleeImpl(BusAttachment& busAttachment, WindDirectionIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of WindDirectionIntfControlleeImpl
     */
    virtual ~WindDirectionIntfControlleeImpl();

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
     * Get HorizontalDirection
     * @return HorizontalDirection
     */
    virtual const uint16_t GetHorizontalDirection () const { return m_HorizontalDirection; }

    /**
     * Set HorizontalDirection
     * @param[in] value
     * @return status
     */
    virtual QStatus SetHorizontalDirection (const uint16_t value);

    /**
     * Get HorizontalMax
     * @return HorizontalMax
     */
    virtual const uint16_t GetHorizontalMax() const { return m_HorizontalMax; }

    /**
     * Set HorizontalMax
     * @param[in] value
     * @return status
     */
    virtual QStatus SetHorizontalMax (const uint16_t value);

    /**
     * Get HorizontalAutoMode
     * @return HorizontalAutoMode
     */
    virtual const uint8_t GetHorizontalAutoMode () const { return m_HorizontalAutoMode; }

    /**
     * Set HorizontalAutoMode
     * @param[in] value
     * @return status
     */
    virtual QStatus SetHorizontalAutoMode (const uint8_t value);


    /**
     * Get VerticalDirection
     * @return VerticalDirection
     */
    virtual const uint16_t GetVerticalDirection () const { return m_VerticalDirection; }

    /**
     * Set VerticalDirection
     * @param[in] value
     * @return status
     */
    virtual QStatus SetVerticalDirection (const uint16_t value);

    /**
     * Get VerticalMax
     * @return VerticalMax
     */
    virtual const uint16_t GetVerticalMax() const { return m_VerticalMax; };

    /**
     * Set VerticalMax
     * @param[in] value
     * @return status
     */
    virtual QStatus SetVerticalMax (const uint16_t value);

    /**
     * Get VerticalAutoMode
     * @return VerticalAutoMode
     */
    virtual const uint8_t GetVerticalAutoMode () const { return m_VerticalAutoMode; }

    /**
     * Set VerticalAutoMode
     * @param[in] value
     * @return status
     */
    virtual QStatus SetVerticalAutoMode (const uint8_t value);


  private:
    WindDirectionIntfControlleeImpl();

    uint16_t adjustHorizontalDirection(uint16_t horizontalDirection);
    bool isHorizontalAutoModeValid(uint8_t horizontalAutoMode);

    uint16_t adjustVerticalDirection(uint16_t verticalDirection);
    bool isVerticalAutoModeValid(uint8_t verticalAutoMode);

    BusAttachment& m_busAttachment;
    WindDirectionIntfControlleeListener& m_interfaceListener;
    uint16_t m_HorizontalDirection;   // read-write, EmitsChangedSignal
    uint16_t m_HorizontalMax;         // read,       EmitsChangedSignal
    uint8_t m_HorizontalAutoMode;     // read-write, EmitsChangedSignal
    uint16_t m_VerticalDirection;   // read-write, EmitsChangedSignal
    uint16_t m_VerticalMax;         // read,       EmitsChangedSignal
    uint8_t m_VerticalAutoMode;     // read-write, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLEEIMPL_H_ */