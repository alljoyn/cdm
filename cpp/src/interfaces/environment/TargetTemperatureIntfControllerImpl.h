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

#ifndef TARGETTEMPERATUREINTFCONTROLLERIMPL_H_
#define TARGETTEMPERATUREINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfController.h>

namespace ajn {
namespace services {

class TargetTemperatureIntfControllerListener;
class CdmProxyBusObject;

/**
 * TargetTemperature Interface Controller implementation class
 */
class TargetTemperatureIntfControllerImpl : public InterfaceController, public TargetTemperatureIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of TargetTemperatureIntfControllerImpl
     */
    TargetTemperatureIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of TargetTemperatureIntfControllerImpl
     */
    virtual ~TargetTemperatureIntfControllerImpl();

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
     * Get current TargetValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetValue(void* context);

    /**
     * Set TargetValue
     * @param[in] TargetValue
     * @param[in] context
     * @return status
     */
    virtual QStatus SetTargetValue(const double value, void* context);

    /**
     * Get MinValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMinValue(void* context);

    /**
     * Get MaxValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxValue(void* context);

    /**
     * Get StepValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetStepValue(void* context);

  private:
    TargetTemperatureIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetStepValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TargetTemperatureIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLERIMPL_H_ */