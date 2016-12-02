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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLERIMPL_H_
#define REMOTECONTROLLABILITYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfController.h>

namespace ajn {
namespace services {

class RemoteControllabilityIntfControllerListener;
class CdmProxyBusObject;

/**
 * RemoteControllability Interface Controller implementation class
 */
class RemoteControllabilityIntfControllerImpl : public InterfaceController, public RemoteControllabilityIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of RemoteControllabilityIntfControllerImpl
     */
    RemoteControllabilityIntfControllerImpl(BusAttachment& busAttachment, RemoteControllabilityIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of RemoteControllabilityIntfControllerImpl
     */
    virtual ~RemoteControllabilityIntfControllerImpl();

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
     * Get isControllable
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsControllable(void* context);


  private:
    RemoteControllabilityIntfControllerImpl();
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetIsControllablePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RemoteControllabilityIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLERIMPL_H_ */