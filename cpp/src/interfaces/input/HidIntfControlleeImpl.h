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

#ifndef HIDINTFCONTROLLEEIMPL_H_
#define HIDINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControllee.h>

namespace ajn {
namespace services {

class HidIntfControlleeListener;
class CdmBusObject;

/**
 * Hid Interface Controllee implementation class
 */
class HidIntfControlleeImpl : public InterfaceControllee, public HidIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of HidIntfControlleeImpl
     */
    HidIntfControlleeImpl(BusAttachment& busAttachment, HidIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of HidIntfControlleeImpl
     */
    virtual ~HidIntfControlleeImpl();

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
     * Set supported events
     * @param[in] supported events
     * @return status
     */
    virtual QStatus SetSupportedEvents(const HidInterface::SupportedInputEvents& supportedEvents);

    /**
     * Get supported events
     * @return mute
     */
    virtual const HidInterface::SupportedInputEvents& GetSupportedEvents() const { return m_supportedEvents; }

    /**
     * Handler of InjectEvents method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnInjectEvents(const InterfaceDescription::Member* member, Message& msg);

  private:
    HidIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    HidIntfControlleeListener& m_interfaceListener;
    SupportedInputEvents m_supportedEvents; // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLEEIMPL_H_ */