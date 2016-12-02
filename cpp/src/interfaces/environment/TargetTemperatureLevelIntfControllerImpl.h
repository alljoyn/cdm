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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfController.h>

namespace ajn {
namespace services {

class TargetTemperatureLevelIntfControllerListener;
class CdmProxyBusObject;

/**
 * TargetTemperatureLevel Interface Controller implementation class
 */
class TargetTemperatureLevelIntfControllerImpl : public InterfaceController, public TargetTemperatureLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of TargetTemperatureLevelIntfControllerImpl
     */
    TargetTemperatureLevelIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of TargetTemperatureLevelIntfControllerImpl
     */
    virtual ~TargetTemperatureLevelIntfControllerImpl();

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
     * Get current TargetLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetLevel(void* context);

    /**
     * Set TargetValue
     * @param[in] value TargetLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus SetTargetLevel(const uint8_t value, void* context);

    /**
     * Get MaxLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxLevel(void* context);

    /**
     * Get SelectableTemperatureLevels
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSelectableTemperatureLevels(void* context);

  private:
    TargetTemperatureLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSelectableTemperatureLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TargetTemperatureLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_ */