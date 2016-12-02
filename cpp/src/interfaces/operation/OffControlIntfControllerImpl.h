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

#ifndef OFFCONTROLINTFCONTROLLERIMPL_H_
#define OFFCONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfController.h>

namespace ajn {
namespace services {

class OffControlIntfControllerListener;
class CdmProxyBusObject;

/**
 * OffControl Interface Controller implementation class
 */
class OffControlIntfControllerImpl : public InterfaceController, public OffControlIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of OffControlIntfControllerImpl
     */
    OffControlIntfControllerImpl(BusAttachment& busAttachment, OffControlIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of OffControlIntfControllerImpl
     */
    virtual ~OffControlIntfControllerImpl();

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
    * Switch Off
    * @param[in] context
    * @return status
    */
    virtual QStatus SwitchOff(void* context);


  private:
    OffControlIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SwitchOffReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    OffControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* OFFCONTROLINTFCONTROLLERIMPL_H_ */