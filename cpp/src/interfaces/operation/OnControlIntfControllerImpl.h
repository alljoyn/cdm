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

#ifndef ONCONTROLINTFCONTROLLERIMPL_H_
#define ONCONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfController.h>

namespace ajn {
namespace services {

class OnControlIntfControllerListener;
class CdmProxyBusObject;

/**
 * OnControl Interface Controller implementation class
 */
class OnControlIntfControllerImpl : public InterfaceController, public OnControlIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of OnControlIntfControllerImpl
     */
    OnControlIntfControllerImpl(BusAttachment& busAttachment, OnControlIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of OnControlIntfControllerImpl
     */
    virtual ~OnControlIntfControllerImpl();

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
    * Switch On
    * @param[in] context
    * @return status
    */
    virtual QStatus SwitchOn(void* context);

  private:
    OnControlIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SwitchOnReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    OnControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ONCONTROLINTFCONTROLLERIMPL_H_ */