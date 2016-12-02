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

#ifndef CURRENTAIRQUALITYINTFCONTROLLERIMPL_H_
#define CURRENTAIRQUALITYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfController.h>

namespace ajn {
namespace services {

class CurrentAirQualityIntfControllerListener;
class CdmProxyBusObject;

/**
 * CurrentAirQuality Interface Controller implementation class
 */
class CurrentAirQualityIntfControllerImpl : public InterfaceController, public CurrentAirQualityIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of CurrentAirQualityIntfControllerImpl
     */
    CurrentAirQualityIntfControllerImpl(BusAttachment& busAttachment, CurrentAirQualityIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of CurrentAirQualityIntfControllerImpl
     */
    virtual ~CurrentAirQualityIntfControllerImpl();

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
     * Get ContaminantType
     * @param[in] context
     * @return status
     */
    QStatus GetContaminantType(void* context);

    /**
     * Get CurrentVale
     * @param[in] context
     * @return status
     */
    QStatus GetCurrentValue(void* context);

    /**
     * Get MaxValue
     * @param[in] context
     * @return status
     */
    QStatus GetMaxValue(void* context);

    /**
     * Get MinValue
     * @param[in] context
     * @return status
     */
    QStatus GetMinValue(void* context);

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
    CurrentAirQualityIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetContaminantTypePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    CurrentAirQualityIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLERIMPL_H_ */