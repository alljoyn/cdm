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

#import "ChannelListener.h"
#import "ChannelViewController.h"
#import "CDMUtil.h"

ChannelListener::ChannelListener(ChannelViewController *viewController):viewController(viewController)
{
    
}

ChannelListener::~ChannelListener()
{
    
}

void ChannelListener::UpdateChannelId(const qcc::String& value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%s", value.c_str()];
    NSLog(@"Got ChannelId: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.channelIdCell.value.text = valueAsStr;
    });
}

void ChannelListener::OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
{
    UpdateChannelId(value);
}

void ChannelListener::OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& value)
{
    UpdateChannelId(value);
}

void ChannelListener::OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetChannelId: succeeded");
    }else {
        NSLog(@"SetChannelId: failed");
    }
}

void ChannelListener::UpdateTotalNumberOfChannels(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got TotalNumberOfChannels: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.totalNumberOfChannelsCell.value.text = valueAsStr;
    });
}

void ChannelListener::OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateTotalNumberOfChannels(value);
}

void ChannelListener::OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateTotalNumberOfChannels(value);
}


void ChannelListener::OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const std::vector<ChannelInfoRecord>& listOfChannelInfoRecords, void* context, const char* errorName, const char* errorMessage)
{
    if(status == ER_OK) {
        NSLog(@"GetChannelList succeeded");
        NSString *builtArgResponseStr = @"";
        std::vector<ChannelInfoRecord>::const_iterator it;
        for(it = listOfChannelInfoRecords.begin(); it != listOfChannelInfoRecords.end(); ++it) {
            NSString *line = [NSString stringWithFormat:@"ID:%s, Number:%s, Name:%s", it->channelID.c_str(), it->channelNumber.c_str(), it->channelName.c_str()];
            builtArgResponseStr = [builtArgResponseStr stringByAppendingString:line];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            viewController.getChannelListOutputCell.output.text = builtArgResponseStr;
        });
    } else {
        NSLog(@"GetChannelList failed");
    }
}

void ChannelListener::OnChannelListChanged(const qcc::String& objectPath)
{
    NSLog(@"Channel list changed at path: %s", objectPath.c_str());
    dispatch_async(dispatch_get_main_queue(), ^{
        [viewController executeMethod:@"GetChannelList"];
    });
}