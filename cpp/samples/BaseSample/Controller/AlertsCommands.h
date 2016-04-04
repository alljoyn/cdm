/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef ALERTSCOMMANDS_H_
#define ALERTSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/AlertsIntfController.h>
#include <alljoyn/hae/interfaces/operation/AlertsIntfControllerListener.h>

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
