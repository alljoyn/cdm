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

#ifndef RAPIDMODETIMEDINTFCONTROLLERIMPL_H_
#define RAPIDMODETIMEDINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfController.h>

namespace ajn {
namespace services {

class RapidModeTimedIntfControllerListener;
class CdmProxyBusObject;

/**
 * RapidModeTimed Interface Controller implementation class
 */
class RapidModeTimedIntfControllerImpl : public InterfaceController, public RapidModeTimedIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of RapidModeTimedIntfControllerImpl
     */
    RapidModeTimedIntfControllerImpl(BusAttachment& busAttachment, RapidModeTimedIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of RapidModeTimedIntfControllerImpl
     */
    virtual ~RapidModeTimedIntfControllerImpl();

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
      * Get rapid mode minutes remaining
      * @param[in] context
      * @return status
     */
    virtual QStatus GetRapidModeMinutesRemaining(void* context);

    /**
     * Set rapid mode minutes remaining
     * @param[in] rapid mode minutes remaining
     * @param[in] context
     * @return status
     */
    virtual QStatus SetRapidModeMinutesRemaining(const uint16_t value, void* context);

    /**
      * Get max set minutes
      * @param[in] context
      * @return status
     */
    virtual QStatus GetMaxSetMinutes(void* context);

  private:
    RapidModeTimedIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetRapidModeMinutesRemainingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetRapidModeMinutesRemainingPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxSetMinutesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RapidModeTimedIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLERIMPL_H_ */