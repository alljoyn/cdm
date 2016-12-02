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

#ifndef OFFCONTROLINTFCONTROLLEEIMPL_H_
#define OFFCONTROLINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllee.h>

namespace ajn {
namespace services {

class OffControlIntfControlleeListener;
class CdmBusObject;

/**
 * OffControl Interface Controllee implementation class
 */
class OffControlIntfControlleeImpl : public InterfaceControllee, public OffControlIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of OffControlIntfControlleeImpl
     */
    OffControlIntfControlleeImpl(BusAttachment& busAttachment, OffControlIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of OffControlIntfControlleeImpl
     */
    virtual ~OffControlIntfControlleeImpl();

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
     * Handler of SwitchOff method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSwitchOff(const InterfaceDescription::Member* member, Message& msg);

  private:
    OffControlIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    OffControlIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* OFFCONTROLINTFCONTROLLEEIMPL_H_ */