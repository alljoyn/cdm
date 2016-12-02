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

#ifndef ALERTSINTFCONTROLLERLISTENER_H_
#define ALERTSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface Controller Listener class
 */
class AlertsIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~AlertsIntfControllerListener() {}

    /**
     * Callback handler for getting Alerts property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] alerts the list of alerts
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const AlertsInterface::Alerts& alerts, void* context) {}

    /**
     * Handler for Alerts property changed
     * @param[in] objectPath the object path
     * @param[in] alerts the list of alerts
     */
    virtual void OnAlertsPropertyChanged(const qcc::String& objectPath, const AlertsInterface::Alerts& alerts) {}

    /**
     * Callback handler for GetAlertCodesDescription method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     * @param[out]descriptions list of alert codes descriptions
     */
    virtual void OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const AlertsInterface::AlertCodesDescription& descriptions,
                                                      void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for AcknowledgeAlert method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for AcknowledgeAllAlerts method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}




};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLERLISTENER_H_ */