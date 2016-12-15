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

#ifndef MoistureOutputLevelListener_h
#define MoistureOutputLevelListener_h

#import "MoistureOutputLevelViewController.h"
#import "alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h"
#import "alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllerListener.h"

class MoistureOutputLevelListener : public ajn::services::MoistureOutputLevelIntfControllerListener
{
    public:
        MoistureOutputLevelListener(MoistureOutputLevelViewController *viewController);
    
        virtual ~MoistureOutputLevelListener();

        virtual void UpdateMoistureOutputLevel(const uint8_t value);
        virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateMaxMoistureOutputLevel(const uint8_t value);
        virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateAutoMode(const AutoMode value);
        virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context);
        virtual void OnAutoModeChanged(const qcc::String& objectPath, const AutoMode value);
        virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context);

        

    private:
        MoistureOutputLevelViewController *viewController;
};

#endif /* MoistureOutputLevelListener_h */