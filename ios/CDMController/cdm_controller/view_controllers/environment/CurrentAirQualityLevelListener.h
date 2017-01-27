////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
// 
//    SPDX-License-Identifier: Apache-2.0
// 
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
// 
//    Copyright 2016 Open Connectivity Foundation and Contributors to
//    AllSeen Alliance. All rights reserved.
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

#ifndef CurrentAirQualityLevelListener_h
#define CurrentAirQualityLevelListener_h

#import "CurrentAirQualityLevelViewController.h"
#import "interfaces/common/environment/CurrentAirQualityLevelInterface.h"
#import "interfaces/controller/environment/CurrentAirQualityLevelIntfControllerListener.h"

using ajn::services::CurrentAirQualityLevelInterface;

class CurrentAirQualityLevelListener : public ajn::services::CurrentAirQualityLevelIntfControllerListener
{
    public:
        CurrentAirQualityLevelListener(CurrentAirQualityLevelViewController *viewController);
    
        virtual ~CurrentAirQualityLevelListener();

        virtual void UpdateContaminantType(const CurrentAirQualityLevelInterface::ContaminantType value);
        virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const CurrentAirQualityLevelInterface::ContaminantType value, void* context);
        virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const CurrentAirQualityLevelInterface::ContaminantType value);

        virtual void UpdateCurrentLevel(const uint8_t value);
        virtual void OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateMaxLevel(const uint8_t value);
        virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value);

        

    private:
        CurrentAirQualityLevelViewController *viewController;
};

#endif /* CurrentAirQualityLevelListener_h */
