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

#ifndef CLOSEDSTATUSINTFCONTROLLERIMPL_H_
#define CLOSEDSTATUSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfController.h>

namespace ajn {
namespace services {

class ClosedStatusIntfControllerListener;
class CdmProxyBusObject;

/**
 * ClosedStatus Interface Controller implementation class
 */
class ClosedStatusIntfControllerImpl : public InterfaceController, public ClosedStatusIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of ClosedStatusIntfControllerImpl
     */
    ClosedStatusIntfControllerImpl(BusAttachment& busAttachment, ClosedStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of ClosedStatusIntfControllerImpl
     */
    virtual ~ClosedStatusIntfControllerImpl();

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
    * Get IsClosed
    * @param[in] context
    * @return status
    */
   virtual QStatus GetIsClosed(void* context);

  private:
    ClosedStatusIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetIsClosedPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    ClosedStatusIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLERIMPL_H_ */