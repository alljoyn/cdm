////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef FilterStatusListener_h
#define FilterStatusListener_h

#import "FilterStatusViewController.h"
#import "alljoyn/cdm/interfaces/operation/FilterStatusInterface.h"
#import "alljoyn/cdm/interfaces/operation/FilterStatusIntfControllerListener.h"

class FilterStatusListener : public ajn::services::FilterStatusIntfControllerListener
{
    public:
        FilterStatusListener(FilterStatusViewController *viewController);
    
        virtual ~FilterStatusListener();

        virtual void UpdateExpectedLifeInDays(const uint16_t value);
        virtual void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value);

        virtual void UpdateIsCleanable(const bool value);
        virtual void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool value, void* context);
        virtual void OnIsCleanableChanged(const qcc::String& objectPath, const bool value);

        virtual void UpdateOrderPercentage(const uint8_t value);
        virtual void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateManufacturer(const qcc::String& value);
        virtual void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context);

        virtual void UpdatePartNumber(const qcc::String& value);
        virtual void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context);

        virtual void UpdateUrl(const qcc::String& value);
        virtual void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context);

        virtual void UpdateLifeRemaining(const uint8_t value);
        virtual void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value);

        

    private:
        FilterStatusViewController *viewController;
};

#endif /* FilterStatusListener_h */