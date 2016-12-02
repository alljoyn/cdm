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

#ifndef ALERTSINTFCONTROLLEE_H_
#define ALERTSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface Controllee class
 */
class AlertsIntfControllee : public AlertsInterface {
  public:
    /**
     * Constructor of AlertsIntfControllee
     */
    AlertsIntfControllee() {}

    /**
     * Destructor of AlertsIntfControllee
     */
    virtual ~AlertsIntfControllee() {}

    /**
     * Get Alerts
     * @return the list of alerts
     */
    virtual const Alerts GetAlerts() const = 0;

    /**
     * Set Alerts
     * @param[in] alerts the list of alerts
     * @return ER_OK on success
     */
    virtual QStatus SetAlerts(const Alerts& alerts) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLEE_H_ */