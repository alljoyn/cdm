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

#ifndef ONOFFSTATUSINTFCONTROLLERIMPL_H_
#define ONOFFSTATUSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfController.h>

namespace ajn {
namespace services {

class OnOffStatusIntfControllerListener;
class CdmProxyBusObject;

/**
 * OnOffStatus Interface Controller implementation class
 */
class OnOffStatusIntfControllerImpl : public InterfaceController, public OnOffStatusIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of OnOffStatusIntfControllerImpl
     */
    OnOffStatusIntfControllerImpl(BusAttachment& busAttachment, OnOffStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of OnOffStatusIntfControllerImpl
     */
    virtual ~OnOffStatusIntfControllerImpl();

    /**
     * Get OnOff
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsOn(void* context);

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
     * TODO: define set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */

    /*
     * TODO: define methods
     */

  private:
    OnOffStatusIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetIsOnPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    OnOffStatusIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ONOFFSTATUSINTFCONTROLLERIMPL_H_ */