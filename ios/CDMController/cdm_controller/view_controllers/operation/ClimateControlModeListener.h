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

#ifndef ClimateControlModeListener_h
#define ClimateControlModeListener_h

#import "ClimateControlModeViewController.h"
#import "alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h"
#import "alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllerListener.h"

class ClimateControlModeListener : public ajn::services::ClimateControlModeIntfControllerListener
{
    public:
        ClimateControlModeListener(ClimateControlModeViewController *viewController);
    
        virtual ~ClimateControlModeListener();

        virtual void UpdateMode(const Mode value);
        virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context);
        virtual void OnModeChanged(const qcc::String& objectPath, const Mode value);
        virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSupportedModes(const std::vector<Mode>& value);
        virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context);
        virtual void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value);

        virtual void UpdateOperationalState(const OperationalState value);
        virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context);
        virtual void OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value);

        

    private:
        ClimateControlModeViewController *viewController;
};

#endif /* ClimateControlModeListener_h */