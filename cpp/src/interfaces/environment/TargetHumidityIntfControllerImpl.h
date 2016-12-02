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

#ifndef TARGETHUMIDITYINTFCONTROLLERIMPL_H_
#define TARGETHUMIDITYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfController.h>

namespace ajn {
namespace services {

class TargetHumidityIntfControllerListener;
class CdmProxyBusObject;

/**
 * TargetHumidity Interface Controller implementation class
 */
class TargetHumidityIntfControllerImpl : public InterfaceController, public TargetHumidityIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of TargetHumidityIntfControllerImpl
     */
    TargetHumidityIntfControllerImpl(BusAttachment& busAttachment, TargetHumidityIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of TargetHumidityIntfControllerImpl
     */
    virtual ~TargetHumidityIntfControllerImpl();

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
    virtual QStatus SetTargetValue(const uint8_t value, void* context);

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

    /**
     * Get SelectableHumidityLevels
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSelectableHumidityLevels(void* context);

  private:
    TargetHumidityIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetStepValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSelectableHumidityLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TargetHumidityIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLERIMPL_H_ */