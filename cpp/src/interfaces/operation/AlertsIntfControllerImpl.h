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

#ifndef ALERTSINTFCONTROLLERIMPL_H_
#define ALERTSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfController.h>

namespace ajn {
namespace services {

class AlertsIntfControllerListener;
class CdmProxyBusObject;

/**
 * Alerts Interface Controller implementation class
 */
class AlertsIntfControllerImpl : public InterfaceController, public AlertsIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of AlertsIntfControllerImpl
     */
    AlertsIntfControllerImpl(BusAttachment& busAttachment, AlertsIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of AlertsIntfControllerImpl
     */
    virtual ~AlertsIntfControllerImpl();

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
     * Get Alerts property
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlerts(void * context = NULL);

    /**
     * Get AlertCodesDescription
     * @param[in] language language
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlertCodesDescription(const qcc::String& language, void* context = NULL);

    /**
     * AcknowledgeAlert
     * @param[in] alertCode alert code
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAlert(const uint16_t alertCode, void * context = NULL);

    /**
     * AcknowledgeAllAlerts
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAllAlerts(void * context = NULL);

  private:
    AlertsIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetAlertsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetAlertCodesDescriptionReplyHandler(Message& message, void* context);
    void AcknowledgeAlertReplyHandler(Message& message, void* context);
    void AcknowledgeAllAlertsReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    AlertsIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLERIMPL_H_ */