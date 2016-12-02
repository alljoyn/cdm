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

#ifndef CURRENTPOWERINTFCONTROLLERIMPL_H_
#define CURRENTPOWERINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfController.h>

namespace ajn {
namespace services {

class CurrentPowerIntfControllerListener;
class CdmProxyBusObject;

/**
 * CurrentPower Interface Controller implementation class
 */
class CurrentPowerIntfControllerImpl : public InterfaceController, public CurrentPowerIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of CurrentPowerIntfControllerImpl
     */
    CurrentPowerIntfControllerImpl(BusAttachment& busAttachment, CurrentPowerIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of CurrentPowerIntfControllerImpl
     */
    virtual ~CurrentPowerIntfControllerImpl();

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
     * Get current CurrentPower
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCurrentPower(void* context);

    /**
     * Get current Precision
     * @param[in] context
     * @return status
     */
    virtual QStatus GetPrecision(void* context);

    /**
     * Get current UpdateMinTime
     * @param[in] context
     * @return status
     */
    virtual QStatus GetUpdateMinTime(void* context);

  private:
    CurrentPowerIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCurrentPowerPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    CurrentPowerIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTPOWERINTFCONTROLLERIMPL_H_ */