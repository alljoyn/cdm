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

#ifndef REPEATMODEINTFCONTROLLERIMPL_H_
#define REPEATMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfController.h>

namespace ajn {
namespace services {

class RepeatModeIntfControllerListener;
class CdmProxyBusObject;

/**
 * RepeatMode Interface Controller implementation class
 */
class RepeatModeIntfControllerImpl : public InterfaceController, public RepeatModeIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of RepeatModeIntfControllerImpl
     */
    RepeatModeIntfControllerImpl(BusAttachment& busAttachment, RepeatModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of RepeatModeIntfControllerImpl
     */
    virtual ~RepeatModeIntfControllerImpl();

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
     * Get RepeatMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetRepeatMode(void* context = NULL);

    /**
     * Set RepeatMode
     * @param[in] RepeatMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetRepeatMode(const bool value, void* context);

  private:
    RepeatModeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void SetRepeatModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetRepeatModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RepeatModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLERIMPL_H_ */