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

#ifndef ALERTSINTFCONTROLLEELISTENER_H_
#define ALERTSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>


namespace ajn {
namespace services {

/**
 * Alerts Interface Controllee Listener class
 */
class AlertsIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of AlertsIntfControlleeListener
     */
    virtual ~AlertsIntfControlleeListener() {}

    /**
     * Handler for getting list of alerts
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] alerts the list of alerts
     * @return ER_OK on success
     */
    virtual QStatus OnGetAlerts(AlertsInterface::Alerts& alerts) = 0;

    /**
     * Handler for GetGetAlertCodesDescription method
     * @param[in] language language
     * @param[out] description alert codes description
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus OnGetAlertCodesDescription(const qcc::String& language, AlertsInterface::AlertCodesDescription& description, ErrorCode& error) = 0;

    /**
     * Handler for AcknowledgeAlert
     * @param[in] alertCode alert code
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus OnAcknowledgeAlert(const uint16_t alertCode, ErrorCode& error) = 0;

    /**
     * Handler for AcknowledgeAllAlerts
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus OnAcknowledgeAllAlerts(ErrorCode& error) = 0;

};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLEELISTENER_H_ */