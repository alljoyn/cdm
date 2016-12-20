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

#ifndef ChannelListener_h
#define ChannelListener_h

#import "ChannelViewController.h"
#import "alljoyn/cdm/interfaces/operation/ChannelInterface.h"
#import "alljoyn/cdm/interfaces/operation/ChannelIntfControllerListener.h"

class ChannelListener : public ajn::services::ChannelIntfControllerListener
{
    public:
        ChannelListener(ChannelViewController *viewController);
    
        virtual ~ChannelListener();

        virtual void UpdateChannelId(const qcc::String& value);
        virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context);
        virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& value);
        virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateTotalNumberOfChannels(const uint16_t value);
        virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t value);

        virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const std::vector<ChannelInfoRecord>& listOfChannelInfoRecords, void* context, const char* errorName, const char* errorMessage);
        
        virtual void OnChannelListChanged(const qcc::String& objectPath);

    private:
        ChannelViewController *viewController;
};

#endif /* ChannelListener_h */