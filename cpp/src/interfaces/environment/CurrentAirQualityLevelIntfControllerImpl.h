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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLERIMPL_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfController.h>

namespace ajn {
namespace services {

class CurrentAirQualityLevelIntfControllerListener;
class CdmProxyBusObject;

/**
 * CurrentAirQualityLevel Interface Controller implementation class
 */
class CurrentAirQualityLevelIntfControllerImpl : public InterfaceController, public CurrentAirQualityLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of CurrentAirQualityLevelIntfControllerImpl
     */
    CurrentAirQualityLevelIntfControllerImpl(BusAttachment& busAttachment, CurrentAirQualityLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of CurrentAirQualityLevelIntfControllerImpl
     */
    virtual ~CurrentAirQualityLevelIntfControllerImpl();

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
    QStatus GetCurrentLevel(void* context);

    /**
     * Get MaxLevel
     * @param[in] context
     * @return status
     */
    QStatus GetMaxLevel(void* context);

  private:
    CurrentAirQualityLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetContaminantTypePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    CurrentAirQualityLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLERIMPL_H_ */