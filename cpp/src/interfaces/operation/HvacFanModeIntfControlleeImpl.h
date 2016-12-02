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

#ifndef HVACFANMODEINTFCONTROLLEEIMPL_H_
#define HVACFANMODEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllee.h>

namespace ajn {
namespace services {

class HvacFanModeIntfControlleeListener;
class CdmBusObject;

/**
 * HvacFanMode interface controllee implementation class
 */
class HvacFanModeIntfControlleeImpl : public InterfaceControllee, public HvacFanModeIntfControllee {
  public:

    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of HvacFanModeIntfControlleeImpl
     */
    HvacFanModeIntfControlleeImpl(BusAttachment& busAttachment, HvacFanModeIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of HvacFanModeIntfControlleeImpl
     */
    virtual ~HvacFanModeIntfControlleeImpl();

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
     * Set Mode
     * @param[in] mode
     * @return status
     */
    virtual QStatus SetMode(const uint16_t mode);

    /**
     * Get Mode
     * @return mode
     */
    virtual const uint16_t GetMode() const { return m_Mode; }

    /**
     * Set SupportedModes
     * @param[in] modes
     * @return status
     */
    virtual QStatus SetSupportedModes(const SupportedModes& modes);

    /**
     * Get SupportedModes
     * @return SupportedModes
     */
    virtual const SupportedModes& GetSupportedModes() const { return m_SupportedModes; }

  private:
    HvacFanModeIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    HvacFanModeIntfControlleeListener& m_interfaceListener;
    uint16_t m_Mode;                       // read-write, EmitsChangedSignal
    SupportedModes m_SupportedModes;         // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* HVACFANMODEINTFCONTROLLEEIMPL_H_ */