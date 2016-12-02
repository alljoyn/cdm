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

#ifndef RESOURCESAVINGINTFCONTROLLERIMPL_H_
#define RESOURCESAVINGINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfController.h>

namespace ajn {
namespace services {

class ResourceSavingIntfControllerListener;
class CdmProxyBusObject;

/**
 * ResourceSaving interface controller implementation class
 */
class ResourceSavingIntfControllerImpl : public InterfaceController, public ResourceSavingIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);


    /**
     * Constructor of ResourceSavingIntfControllerImpl
     */
    ResourceSavingIntfControllerImpl(BusAttachment& busAttachment, ResourceSavingIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of ResourceSavingIntfControlleeImpl
     */
    virtual ~ResourceSavingIntfControllerImpl();

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
     * Set ResouceSaving Mode
     * @param[in] mode
     * @return status
     */
    virtual QStatus SetResourceSavingMode(const bool mode, void* context );

    /**
     * Get ResourceSaving mode
     * @return ResourceSavingMode
     */
    virtual QStatus GetResourceSavingMode( void* context );

  private:
    ResourceSavingIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    ResourceSavingIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLERIMPL_H_ */