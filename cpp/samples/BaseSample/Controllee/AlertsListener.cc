/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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