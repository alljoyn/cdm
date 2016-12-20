////////////////////////////////////////////////////////////////////////////////
//    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//    PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef AudioVideoInputListener_h
#define AudioVideoInputListener_h

#import "AudioVideoInputViewController.h"
#import "alljoyn/cdm/interfaces/operation/AudioVideoInputInterface.h"
#import "alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControllerListener.h"

class AudioVideoInputListener : public ajn::services::AudioVideoInputIntfControllerListener
{
    public:
        using InputSources = ajn::services::AudioVideoInputInterface::InputSources;
    
        AudioVideoInputListener(AudioVideoInputViewController *viewController);
    
        virtual ~AudioVideoInputListener();

        virtual void UpdateInputSourceId(const uint16_t value);
        virtual void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnInputSourceIdChanged(const qcc::String& objectPath, const uint16_t value);
        virtual void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSupportedInputSources(const InputSources& value);
        virtual void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const InputSources& value, void* context);
        virtual void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const InputSources& value);

        

    private:
        AudioVideoInputViewController *viewController;
};

#endif /* AudioVideoInputListener_h */