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

#ifndef FANSPEEDLEVELINTFCONTROLLERIMPL_H_
#define FANSPEEDLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfController.h>

namespace ajn {
namespace services {

class FanSpeedLevelIntfControllerListener;
class CdmProxyBusObject;

/**
 * FanSpeedLevel Interface Controller implementation class
 */
class FanSpeedLevelIntfControllerImpl : public InterfaceController, public FanSpeedLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of FanSpeedLevelIntfControllerImpl
     */
    FanSpeedLevelIntfControllerImpl(BusAttachment& busAttachment, FanSpeedLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of FanSpeedLevelIntfControllerImpl
     */
    virtual ~FanSpeedLevelIntfControllerImpl();

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
     * Get current FanSpeedLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetFanSpeedLevel(void* context);

    /**
     * Set FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus SetFanSpeedLevel(const uint8_t value, void* context);

    /**
     * Get MaxFanSpeedLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxFanSpeedLevel(void* context);

    /**
     * Get current AutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetAutoMode(void* context);

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetAutoMode(const uint8_t value, void* context);

  private:
    FanSpeedLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void SetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    FanSpeedLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLERIMPL_H_ */