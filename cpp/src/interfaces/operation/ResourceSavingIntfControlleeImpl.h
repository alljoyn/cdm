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

#ifndef RESOURCESAVINGINTFCONTROLLEEIMPL_H_
#define RESOURCESAVINGINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfControllee.h>

namespace ajn {
namespace services {

class ResourceSavingIntfControlleeListener;
class CdmBusObject;

/**
 * ResourceSaving interface controllee implementation class
 */
class ResourceSavingIntfControlleeImpl : public InterfaceControllee, public ResourceSavingIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);


    /**
     * Constructor of ResourceSavingIntfControlleeImpl
     */
    ResourceSavingIntfControlleeImpl(BusAttachment& busAttachment, ResourceSavingIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of ResourceSavingIntfControlleeImpl
     */
    virtual ~ResourceSavingIntfControlleeImpl();

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
     * Set ResouceSaving Mode
     * @param[in] mode
     * @return status
     */
    virtual QStatus SetResourceSavingMode(const bool mode);

    /**
     * Get ResourceSaving mode
     * @return ResourceSavingMode
     */
    virtual const bool GetResourceSavingMode() const { return m_ResourceSavingMode; }


  private:
    ResourceSavingIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    ResourceSavingIntfControlleeListener& m_interfaceListener;
    bool m_ResourceSavingMode;          // read-write, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLEEIMPL_H_ */