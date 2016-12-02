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

#ifndef ALERTSCOMMANDS_H_
#define ALERTSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AlertsIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class AlertsListener : public AlertsIntfControllerListener{
  public:
    AlertsListener();
    virtual ~AlertsListener();

    virtual void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const AlertsInterface::Alerts& alerts, void* context);
    virtual void OnAlertsPropertyChanged(const qcc::String& objectPath, const AlertsInterface::Alerts& alerts);
    virtual void OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const AlertsInterface::AlertCodesDescription& descriptions,void* context, const char* errorName, const char* errorMessage);
    virtual void OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
    virtual void OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
};

class AlertsCommands : public InterfaceCommands
{
  public:
    AlertsCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~AlertsCommands();

    virtual void Init();

    AlertsIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetAlerts(Commands* commands, std::string& cmd);

    static void OnCmdGetAlertCodesDescription(Commands* commands, std::string& cmd);

    static void OnCmdAcknowledgeAlert(Commands* commands, std::string& cmd);
    static void OnCmdAcknowledgeAllAlerts(Commands* commands, std::string& cmd);
  private:
    AlertsIntfController* m_intfController;
    AlertsListener m_listener;
};


#endif /* ALERTSCOMMANDS_H_ */