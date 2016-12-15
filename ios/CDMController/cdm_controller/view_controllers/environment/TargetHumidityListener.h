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

#ifndef TargetHumidityListener_h
#define TargetHumidityListener_h

#import "TargetHumidityViewController.h"
#import "alljoyn/cdm/interfaces/environment/TargetHumidityInterface.h"
#import "alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllerListener.h"

class TargetHumidityListener : public ajn::services::TargetHumidityIntfControllerListener
{
    public:
        TargetHumidityListener(TargetHumidityViewController *viewController);
    
        virtual ~TargetHumidityListener();

        virtual void UpdateTargetValue(const uint8_t value);
        virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateMinValue(const uint8_t value);
        virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMinValueChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateMaxValue(const uint8_t value);
        virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateStepValue(const uint8_t value);
        virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnStepValueChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateSelectableHumidityLevels(const std::vector<uint8_t>& value);
        virtual void OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);
        virtual void OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value);

        

    private:
        TargetHumidityViewController *viewController;
};

#endif /* TargetHumidityListener_h */