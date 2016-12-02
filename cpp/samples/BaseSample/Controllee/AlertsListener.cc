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

#include <iostream>
#include "AlertsListener.h"

using namespace std;


QStatus AlertsListener::OnGetAlerts(AlertsInterface::Alerts& alerts)
{
    QStatus status = ER_OK;
    cout << "AlertsListener::OnGetAlerts" << endl;
    for(size_t i = 0; i < alerts.size(); i++)
    {
        cout << "severity: " << alerts[i].severity << " - alertCode: " << alerts[i].alertCode << " - needAcknowledgement: " << (alerts[i].needAcknowledgement ? "true" : "false") << endl;
    }
    return status;
}

QStatus AlertsListener::OnGetAlertCodesDescription(const qcc::String& language, AlertsInterface::AlertCodesDescription& description, ErrorCode& error)
{
    cout << "AlertsListener::OnGetAlertCodesDescription" << endl;
    QStatus status = ER_OK;
    if(language == "en")
    {
        AlertsInterface::AlertCodeDescriptor desc;
        desc.code = 0x8000;
        desc.description = "alert code 0x8000";
        description.push_back(desc);
        desc.code = 0x8001;
        desc.description = "alert code 0x8001";
        description.push_back(desc);
        desc.code = 0x8002;
        desc.description = "alert code 0x8002";
        description.push_back(desc);
    }
    else 
    {
        error = LANGUAGE_NOT_SUPPORTED;
        status = ER_LANGUAGE_NOT_SUPPORTED;
    }
    return status;
}

QStatus AlertsListener::OnAcknowledgeAlert(const uint16_t alertCode, ErrorCode& error)
{
    QStatus status = ER_OK;
    cout << "AlertsListener::OnAcknowledgeAlert" << endl;
    cout << "alertCode: " <<(int)alertCode << endl;
    error = ErrorCode::NOT_ERROR;
    return status;
}

QStatus AlertsListener::OnAcknowledgeAllAlerts(ErrorCode& error)
{
    QStatus status = ER_OK;
    cout << "AlertsListener::OnAcknowledgeAllAlerts" << endl;
    error = ErrorCode::NOT_ERROR;
    return status;
}