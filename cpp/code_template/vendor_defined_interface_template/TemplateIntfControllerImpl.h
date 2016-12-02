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

#ifndef {interface_nameu}INTFCONTROLLERIMPL_H_
#define {interface_nameu}INTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include "{interface_name}IntfController.h"

namespace ajn {
namespace services {

class {interface_name}IntfControllerListener;
class CdmProxyBusObject;

/**
 * {interface_name} Interface Controller implementation class
 */
class {interface_name}IntfControllerImpl : public InterfaceController, public {interface_name}IntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of {interface_name}IntfControllerImpl
     */
    {interface_name}IntfControllerImpl(BusAttachment& busAttachment, {interface_name}IntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of {interface_name}IntfControllerImpl
     */
    virtual ~{interface_name}IntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * TODO: define functions to request the set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */

    /*
     * TODO: define functions to request the method call
     */


  private:
    {interface_name}IntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    /*
     * TODO: define set/get properties async callback
     */

    /*
     * TODO: define method reply handler
     */

    /*
     * TODO: define signal handler
     */

    BusAttachment& m_busAttachment;
    {interface_name}IntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLERIMPL_H_ */