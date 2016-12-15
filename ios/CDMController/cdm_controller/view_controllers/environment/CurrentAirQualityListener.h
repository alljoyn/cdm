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

#ifndef CurrentAirQualityListener_h
#define CurrentAirQualityListener_h

#import "CurrentAirQualityViewController.h"
#import "alljoyn/cdm/interfaces/environment/CurrentAirQualityInterface.h"
#import "alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllerListener.h"

class CurrentAirQualityListener : public ajn::services::CurrentAirQualityIntfControllerListener
{
    public:
        CurrentAirQualityListener(CurrentAirQualityViewController *viewController);
    
        virtual ~CurrentAirQualityListener();

        virtual void UpdateContaminantType(const ContaminantType value);
        virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context);
        virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value);

        virtual void UpdateCurrentValue(const double value);
        virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value);

        virtual void UpdateMinValue(const double value);
        virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnMinValueChanged(const qcc::String& objectPath, const double value);

        virtual void UpdateMaxValue(const double value);
        virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value);

        virtual void UpdatePrecision(const double value);
        virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value);

        virtual void UpdateUpdateMinTime(const uint16_t value);
        virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value);

        

    private:
        CurrentAirQualityViewController *viewController;
};

#endif /* CurrentAirQualityListener_h */