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

#ifndef VENDORDEFINEDINTFCONTROLLEEIMPL_H_
#define VENDORDEFINEDINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include "VendorDefinedIntfControllee.h"

namespace ajn {
namespace services {

class VendorDefinedIntfControlleeListener;
class CdmBusObject;

/**
 * VendorDefined Interface Controllee implementation class
 */
class VendorDefinedIntfControlleeImpl : public InterfaceControllee, public VendorDefinedIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of VendorDefinedIntfControlleeImpl
     */
    VendorDefinedIntfControlleeImpl(BusAttachment& busAttachment, VendorDefinedIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of VendorDefinedIntfControlleeImpl
     */
    virtual ~VendorDefinedIntfControlleeImpl();

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
     * TODO: define functions that set/get property
     */
    virtual QStatus SetTestProperty(int32_t property);
    virtual int32_t GetTestProperty() const { return m_testProperty; }

    /**
     * TODO: define functions that can emit signals
     */
    virtual QStatus EmitTestSignal();

    /**
     * TODO: define functions that receives the method call
     */
    void OnTestMethod(const InterfaceDescription::Member* member, Message& msg);

  private:
    VendorDefinedIntfControlleeImpl();
    BusAttachment& m_busAttachment;
    VendorDefinedIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    int32_t m_testProperty;
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLEEIMPL_H_ */