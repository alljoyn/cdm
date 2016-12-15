////////////////////////////////////////////////////////////////////////////////
// //    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef AlertsListener_h
#define AlertsListener_h

#import "AlertsViewController.h"
#import "alljoyn/cdm/interfaces/operation/AlertsInterface.h"
#import "alljoyn/cdm/interfaces/operation/AlertsIntfControllerListener.h"

class AlertsListener : public ajn::services::AlertsIntfControllerListener
{
    public:
        AlertsListener(AlertsViewController *viewController);
    
        virtual ~AlertsListener();

        virtual void UpdateAlerts(const std::vector<AlertRecord>& value);
        virtual void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const std::vector<AlertRecord>& value, void* context);
        virtual void OnAlertsChanged(const qcc::String& objectPath, const std::vector<AlertRecord>& value);

        virtual void OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const std::vector<AlertCodesDescriptor>& description, void* context, const char* errorName, const char* errorMessage);
        virtual void OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
        virtual void OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
        

    private:
        AlertsViewController *viewController;
};

#endif /* AlertsListener_h */