////////////////////////////////////////////////////////////////////////////////
// 
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

#import "HidListener.h"
#import "HidViewController.h"
#import "CDMUtil.h"

HidListener::HidListener(HidViewController *viewController):viewController(viewController)
{
    
}

HidListener::~HidListener()
{
    
}

void HidListener::UpdateSupportedEvents(const std::vector<HidInterface::SupportedInputEvent>& value)
{
    NSString *valueArrayAsString = @"";
    std::vector<HidInterface::SupportedInputEvent>::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%u,%u,%d,%d ", it->type, it->code, it->min, it->max]];
        ++it;
    }
    NSLog(@"Got SupportedEvents: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.supportedEventsCell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
}

void HidListener::OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const std::vector<HidInterface::SupportedInputEvent>& value, void* context)
{
    UpdateSupportedEvents(value);
}

void HidListener::OnSupportedEventsChanged(const qcc::String& objectPath, const std::vector<HidInterface::SupportedInputEvent>& value)
{
    UpdateSupportedEvents(value);
}


void HidListener::OnResponseInjectEvents(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"InjectEvents succeeded");
    } else {
        NSLog(@"InjectEvents failed");
    }
}

