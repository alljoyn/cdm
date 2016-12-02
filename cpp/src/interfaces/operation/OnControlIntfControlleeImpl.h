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

#ifndef ONCONTROLINTFCONTROLLEEIMPL_H_
#define ONCONTROLINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllee.h>

namespace ajn {
namespace services {

class OnControlIntfControlleeListener;
class CdmBusObject;

/**
 * OnControl Interface Controllee implementation class
 */
class OnControlIntfControlleeImpl : public InterfaceControllee, public OnControlIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of OnControlIntfControlleeImpl
     */
    OnControlIntfControlleeImpl(BusAttachment& busAttachment, OnControlIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of OnControlIntfControlleeImpl
     */
    virtual ~OnControlIntfControlleeImpl();

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
     * Handler of SwitchOn method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSwitchOn(const InterfaceDescription::Member* member, Message& msg);

  private:
    OnControlIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    OnControlIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* ONCONTROLINTFCONTROLLEEIMPL_H_ */