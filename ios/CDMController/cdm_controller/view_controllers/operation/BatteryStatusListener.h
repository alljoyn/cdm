////////////////////////////////////////////////////////////////////////////////
// // Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef BatteryStatusListener_h
#define BatteryStatusListener_h

#import "BatteryStatusViewController.h"
#import "alljoyn/cdm/interfaces/operation/BatteryStatusInterface.h"
#import "alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllerListener.h"

class BatteryStatusListener : public ajn::services::BatteryStatusIntfControllerListener
{
    public:
        BatteryStatusListener(BatteryStatusViewController *viewController);
    
        virtual ~BatteryStatusListener();

        virtual void UpdateCurrentValue(const uint8_t value);
        virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateIsCharging(const bool value);
        virtual void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool value, void* context);
        virtual void OnIsChargingChanged(const qcc::String& objectPath, const bool value);

        

    private:
        BatteryStatusViewController *viewController;
};

#endif /* BatteryStatusListener_h */