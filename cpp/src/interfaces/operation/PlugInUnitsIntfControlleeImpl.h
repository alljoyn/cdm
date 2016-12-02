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

#ifndef PLUGINUNITSINTFCONTROLLEEIMPL_H_
#define PLUGINUNITSINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControllee.h>

namespace ajn {
namespace services {

class PlugInUnitsIntfControlleeListener;
class CdmBusObject;

/**
 * PlugInUnits Interface Controllee implementation class
 */
class PlugInUnitsIntfControlleeImpl : public InterfaceControllee, public PlugInUnitsIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of PlugInUnitsIntfControlleeImpl
     */
    PlugInUnitsIntfControlleeImpl(BusAttachment& busAttachment, PlugInUnitsIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of PlugInUnitsIntfControlleeImpl
     */
    virtual ~PlugInUnitsIntfControlleeImpl();

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
     * Get PlugInUnits
     * @return the list of plug in units
     */
    virtual const PlugInUnits& GetPlugInUnits() const { return m_plugInUnits; }

    /**
     * Set PlugInUnits
     * @param[in]  plugInUnits the list of plug in unints
     * @return ER_OK on success
     */
    virtual QStatus SetPlugInUnits(const PlugInUnits& units);

  private:
    PlugInUnitsIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    PlugInUnitsIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    PlugInUnits m_plugInUnits;
};

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTFCONTROLLEEIMPL_H_ */