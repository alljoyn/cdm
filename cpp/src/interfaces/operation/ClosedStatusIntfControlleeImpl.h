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

#ifndef CLOSEDSTATUSINTFCONTROLLEEIMPL_H_
#define CLOSEDSTATUSINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllee.h>

namespace ajn {
namespace services {

class ClosedStatusIntfControlleeListener;
class CdmBusObject;

/**
 * ClosedStatus Interface Controllee implementation class
 */
class ClosedStatusIntfControlleeImpl : public InterfaceControllee, public ClosedStatusIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of ClosedStatusIntfControlleeImpl
     */
    ClosedStatusIntfControlleeImpl(BusAttachment& busAttachment, ClosedStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of ClosedStatusIntfControlleeImpl
     */
    virtual ~ClosedStatusIntfControlleeImpl();

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
     * Set IsClosed
     * @param[in] isClosed
     * @return status
     */
    virtual QStatus SetIsClosed(const bool isClosed);

    /**
     * Get IsClosed
     * @return IsClosed
     */
    virtual const bool GetIsClosed() const { return m_isClosed; }

  private:
    ClosedStatusIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    ClosedStatusIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    bool m_isClosed;
};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLEEIMPL_H_ */