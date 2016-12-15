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

#ifndef WindDirectionListener_h
#define WindDirectionListener_h

#import "WindDirectionViewController.h"
#import "alljoyn/cdm/interfaces/environment/WindDirectionInterface.h"
#import "alljoyn/cdm/interfaces/environment/WindDirectionIntfControllerListener.h"

class WindDirectionListener : public ajn::services::WindDirectionIntfControllerListener
{
    public:
        WindDirectionListener(WindDirectionViewController *viewController);
    
        virtual ~WindDirectionListener();

        virtual void UpdateHorizontalDirection(const uint16_t value);
        virtual void OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value);
        virtual void OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateHorizontalMax(const uint16_t value);
        virtual void OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value);

        virtual void UpdateHorizontalAutoMode(const AutoMode value);
        virtual void OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context);
        virtual void OnHorizontalAutoModeChanged(const qcc::String& objectPath, const AutoMode value);
        virtual void OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateVerticalDirection(const uint16_t value);
        virtual void OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value);
        virtual void OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateVerticalMax(const uint16_t value);
        virtual void OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value);

        virtual void UpdateVerticalAutoMode(const AutoMode value);
        virtual void OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context);
        virtual void OnVerticalAutoModeChanged(const qcc::String& objectPath, const AutoMode value);
        virtual void OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context);

        

    private:
        WindDirectionViewController *viewController;
};

#endif /* WindDirectionListener_h */