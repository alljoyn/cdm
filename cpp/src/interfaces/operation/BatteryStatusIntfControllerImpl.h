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

#ifndef BATTERYSTATUSINTFCONTROLLERIMPL_H_
#define BATTERYSTATUSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfController.h>

namespace ajn {
namespace services {

class BatteryStatusIntfControllerListener;
class CdmProxyBusObject;

/**
 * BatteryStatus Interface Controller implementation class
 */
class BatteryStatusIntfControllerImpl : public InterfaceController, public BatteryStatusIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of BatteryStatusIntfControllerImpl
     */
    BatteryStatusIntfControllerImpl(BusAttachment& busAttachment, BatteryStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of BatteryStatusIntfControllerImpl
     */
    virtual ~BatteryStatusIntfControllerImpl();

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
     * Get current value of battery status
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCurrentValue(void* context);

    /**
     * Get if battery is being charged
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsCharging(void* context);

  private:
    BatteryStatusIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetIsChargingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    BatteryStatusIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLERIMPL_H_ */