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

#ifndef PLUGINUNITSINTFCONTROLLERIMPL_H_
#define PLUGINUNITSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfController.h>

namespace ajn {
namespace services {

class PlugInUnitsIntfControllerListener;
class CdmProxyBusObject;

/**
 * PlugInUnits Interface Controller implementation class
 */
class PlugInUnitsIntfControllerImpl : public InterfaceController, public PlugInUnitsIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of PlugInUnitsIntfControllerImpl
     */
    PlugInUnitsIntfControllerImpl(BusAttachment& busAttachment, PlugInUnitsIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of PlugInUnitsIntfControllerImpl
     */
    virtual ~PlugInUnitsIntfControllerImpl();

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
     * Get PlugInUnits
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPlugInUnits(void* context = NULL);

  private:
    PlugInUnitsIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetPlugInUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    PlugInUnitsIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTFCONTROLLERIMPL_H_ */