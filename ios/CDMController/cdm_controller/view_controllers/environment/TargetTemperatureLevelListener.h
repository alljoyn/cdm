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

#ifndef TargetTemperatureLevelListener_h
#define TargetTemperatureLevelListener_h

#import "TargetTemperatureLevelViewController.h"
#import "alljoyn/cdm/interfaces/environment/TargetTemperatureLevelInterface.h"
#import "alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllerListener.h"

class TargetTemperatureLevelListener : public ajn::services::TargetTemperatureLevelIntfControllerListener
{
    public:
        TargetTemperatureLevelListener(TargetTemperatureLevelViewController *viewController);
    
        virtual ~TargetTemperatureLevelListener();

        virtual void UpdateMaxLevel(const uint8_t value);
        virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateTargetLevel(const uint8_t value);
        virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSelectableTemperatureLevels(const std::vector<uint8_t>& value);
        virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);
        virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value);

        

    private:
        TargetTemperatureLevelViewController *viewController;
};

#endif /* TargetTemperatureLevelListener_h */