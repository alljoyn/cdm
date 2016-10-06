/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "AlertsCommands.h"
#include "ControllerSample.h"

AlertsListener::AlertsListener()
{
}

AlertsListener::~AlertsListener()
{
}


void AlertsListener::OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const AlertsInterface::Alerts& alerts, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# alerts: " << endl;
    for(size_t i = 0; i < alerts.size(); i++)
        cout << "severity: " << (int)alerts[i].severity << " - alertCode: " << alerts[i].alertCode << " - needAcknowledgement: " << (alerts[i].needAcknowledgement ? "true" : "false") << endl;
}
void AlertsListener::OnAlertsPropertyChanged(const qcc::String& objectPath, const AlertsInterface::Alerts& alerts)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# alerts: " << endl;
    for(size_t i = 0; i < alerts.size(); i++)
        cout << "severity: " << (int)alerts[i].severity << " - alertCode: " << alerts[i].alertCode << " - needAcknowledgement: " << (alerts[i].needAcknowledgement ? "true" : "false") << endl;
}
void AlertsListener::OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const AlertsInterface::AlertCodesDescription& descriptions, void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# alert codes descs: " << endl;
    if(status != ER_OK)
    {
        cout << "error name: " << errorName << endl;
        cout << "error mess: " << errorMessage << endl;
    }
    for(size_t i = 0 ; i < descriptions.size(); i++)
        cout << (int)descriptions[i].code << " - " << descriptions[i].description << endl;
}
void AlertsListener::OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    if(status != ER_OK)
    {
        cout << "error name: " << errorName << endl;
        cout << "error mess: " << errorMessage << endl;
    }
}
void AlertsListener::OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    if(status != ER_OK)
    {
        cout << "error name: " << errorName << endl;
        cout << "error mess: " << errorMessage << endl;
    }
}


AlertsCommands::AlertsCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

AlertsCommands::~AlertsCommands()
{

}

void AlertsCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ALERTS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<AlertsIntfController*>(cdmInterface);
    }

    RegisterCommand(&AlertsCommands::OnCmdGetAlerts, "ga", "get alerts");
    RegisterCommand(&AlertsCommands::OnCmdGetAlertCodesDescription, "gacd", "get alert codes description");
    RegisterCommand(&AlertsCommands::OnCmdAcknowledgeAlert, "ack", "acknowledge alert (use ack <alertCode>)");
    RegisterCommand(&AlertsCommands::OnCmdAcknowledgeAllAlerts, "ackall", "acknowledge all alerts");
    PrintCommands();
}
void AlertsCommands::OnCmdGetAlerts(Commands* commands, std::string& cmd)
{
    AlertsIntfController* intfController = static_cast<AlertsCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetAlerts();
}

void AlertsCommands::OnCmdGetAlertCodesDescription(Commands* commands, std::string& cmd)
{
    AlertsIntfController* intfController = static_cast<AlertsCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetAlertCodesDescription(cmd.c_str());
}

void AlertsCommands::OnCmdAcknowledgeAlert(Commands* commands, std::string& cmd)
{
    AlertsIntfController* intfController = static_cast<AlertsCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int code = strtol(cmd.c_str(), NULL, 10);

    intfController->AcknowledgeAlert(code);
}

void AlertsCommands::OnCmdAcknowledgeAllAlerts(Commands* commands, std::string& cmd)
{
    AlertsIntfController* intfController = static_cast<AlertsCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->AcknowledgeAllAlerts();
}