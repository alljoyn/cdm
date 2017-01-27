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

#ifndef TargetTemperatureListener_h
#define TargetTemperatureListener_h

#import "TargetTemperatureViewController.h"
#import "interfaces/common/environment/TargetTemperatureInterface.h"
#import "interfaces/controller/environment/TargetTemperatureIntfControllerListener.h"

using ajn::services::TargetTemperatureInterface;

class TargetTemperatureListener : public ajn::services::TargetTemperatureIntfControllerListener
{
    public:
        TargetTemperatureListener(TargetTemperatureViewController *viewController);
    
        virtual ~TargetTemperatureListener();

        virtual void UpdateTargetValue(const double value);
        virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnTargetValueChanged(const qcc::String& objectPath, const double value);
        virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateMinValue(const double value);
        virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnMinValueChanged(const qcc::String& objectPath, const double value);

        virtual void UpdateMaxValue(const double value);
        virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value);

        virtual void UpdateStepValue(const double value);
        virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnStepValueChanged(const qcc::String& objectPath, const double value);

        

    private:
        TargetTemperatureViewController *viewController;
};

#endif /* TargetTemperatureListener_h */
