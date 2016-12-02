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

#ifndef HVACFANMODEINTFCONTROLLERIMPL_H_
#define HVACFANMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfController.h>

namespace ajn {
namespace services {

class HvacFanModeIntfControllerListener;
class CdmProxyBusObject;

/**
 * HvacFanMode interface controllee implementation class
 */
class HvacFanModeIntfControllerImpl : public InterfaceController, public HvacFanModeIntfController {
  public:

    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Constructor of HvacFanModeIntfControllerImpl
     */
    HvacFanModeIntfControllerImpl(BusAttachment& busAttachment, HvacFanModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Destructor of HvacFanModeIntfControllerImpl
     */
    virtual ~HvacFanModeIntfControllerImpl();

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
     * Get current Mode status
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMode(void* context);

    /**
     * Set Mode
     * @param[in] Mode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetMode(const uint16_t mode, void* context);

    /**
     * Get SupportedModes
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedModes(void* context);

  private:
    HvacFanModeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedModesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    HvacFanModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* HVACFANMODEINTFCONTROLLERIMPL_H_ */