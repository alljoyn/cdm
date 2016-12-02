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

#ifndef RAPIDMODEINTFCONTROLLEEIMPL_H_
#define RAPIDMODEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControllee.h>

namespace ajn {
namespace services {

class RapidModeIntfControlleeListener;
class CdmBusObject;

/**
 * RapidMode Interface Controllee implementation class
 */
class RapidModeIntfControlleeImpl : public InterfaceControllee, public RapidModeIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of RapidModeIntfControlleeImpl
     */
    RapidModeIntfControlleeImpl(BusAttachment& busAttachment, RapidModeIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of RapidModeIntfControlleeImpl
     */
    virtual ~RapidModeIntfControlleeImpl();

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
     * Get RapidMode
     * @return rapid mode
     */
    virtual const bool GetRapidMode() const { return m_rapidMode; }

    /**
     * Set RapidMode
     * @param[in] rapid mode
     * @return ER_OK on successful
     */
    virtual QStatus SetRapidMode(const bool rapidMode);

  private:
    RapidModeIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    RapidModeIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    bool m_rapidMode;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLEEIMPL_H_ */