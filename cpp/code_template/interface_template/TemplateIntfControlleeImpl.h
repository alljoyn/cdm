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

#ifndef {interface_nameu}INTFCONTROLLEEIMPL_H_
#define {interface_nameu}INTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/{interface_category}/{interface_name}IntfControllee.h>

namespace ajn {
namespace services {

class {interface_name}IntfControlleeListener;
class CdmBusObject;

/**
 * {interface_name} Interface Controllee implementation class
 */
class {interface_name}IntfControlleeImpl : public InterfaceControllee, public {interface_name}IntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of {interface_name}IntfControlleeImpl
     */
    {interface_name}IntfControlleeImpl(BusAttachment& busAttachment, {interface_name}IntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of {interface_name}IntfControlleeImpl
     */
    virtual ~{interface_name}IntfControlleeImpl();

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
     * TODO: define functions that set/get properties
     */

    /**
     * TODO: define functions that can emit signals, if any
     */

    /**
     * TODO: define functions that receives the method call
     */
  private:
    {interface_name}IntfControlleeImpl();

    BusAttachment& m_busAttachment;
    {interface_name}IntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLEEIMPL_H_ */