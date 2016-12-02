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

#ifndef ALERTSINTFCONTROLLER_H_
#define ALERTSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface Controller class
 */
class AlertsIntfController : public AlertsInterface {
  public:
    /**
     * Constructor of AlertsIntfController
     */
    AlertsIntfController() {}

    /**
     * Destructor of AlertsIntfController
     */
    virtual ~AlertsIntfController() {}

    /**
     * Get Alerts property
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlerts(void * context = NULL) = 0;

    /**
     * Get AlertCodesDescription
     * @param[in] language language
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlertCodesDescription(const qcc::String& language, void* context = NULL) = 0;

    /**
     * AcknowledgeAlert
     * @param[in] alertCode alert code
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAlert(const uint16_t alertCode, void * context = NULL) = 0;

    /**
     * AcknowledgeAllAlerts
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAllAlerts(void * context = NULL) = 0;



};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLER_H_ */