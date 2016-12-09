////////////////////////////////////////////////////////////////////////////////
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

#ifndef TimerListener_h
#define TimerListener_h

#import "TimerViewController.h"
#import "alljoyn/cdm/interfaces/operation/TimerInterface.h"
#import "alljoyn/cdm/interfaces/operation/TimerIntfControllerListener.h"

class TimerListener : public ajn::services::TimerIntfControllerListener
{
    public:
        TimerListener(TimerViewController *viewController);
    
        virtual ~TimerListener();

        virtual void UpdateReferenceTimer(const int32_t value);
        virtual void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, const int32_t value, void* context);

        virtual void UpdateTargetTimeToStart(const int32_t value);
        virtual void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, const int32_t value, void* context);
        virtual void OnTargetTimeToStartChanged(const qcc::String& objectPath, const int32_t value);

        virtual void UpdateTargetTimeToStop(const int32_t value);
        virtual void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, const int32_t value, void* context);
        virtual void OnTargetTimeToStopChanged(const qcc::String& objectPath, const int32_t value);

        virtual void UpdateEstimatedTimeToEnd(const int32_t value);
        virtual void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, const int32_t value, void* context);

        virtual void UpdateRunningTime(const int32_t value);
        virtual void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, const int32_t value, void* context);

        virtual void UpdateTargetDuration(const int32_t value);
        virtual void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, const int32_t value, void* context);
        virtual void OnTargetDurationChanged(const qcc::String& objectPath, const int32_t value);

        virtual void OnResponseSetTargetTimeToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
        virtual void OnResponseSetTargetTimeToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
        

    private:
        TimerViewController *viewController;
};

#endif /* TimerListener_h */