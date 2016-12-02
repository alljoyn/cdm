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

#ifndef ALERTSLISTENER_H_
#define ALERTSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AlertsIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfControlleeListener.h>

using namespace ajn;
using namespace services;


class AlertsListener : public AlertsIntfControlleeListener
{
public:

    virtual QStatus OnGetAlerts(AlertsInterface::Alerts& alerts);

    virtual QStatus OnGetAlertCodesDescription(const qcc::String& language, AlertsInterface::AlertCodesDescription& description, ErrorCode& error);

    virtual QStatus OnAcknowledgeAlert(const uint16_t alertCode, ErrorCode& error);

    virtual QStatus OnAcknowledgeAllAlerts(ErrorCode& error);

};

#endif /* ALERTSLISTENER_H_ */