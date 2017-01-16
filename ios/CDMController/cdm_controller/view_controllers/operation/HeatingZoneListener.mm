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

#import "HeatingZoneListener.h"
#import "HeatingZoneViewController.h"
#import "CDMUtil.h"

HeatingZoneListener::HeatingZoneListener(HeatingZoneViewController *viewController):viewController(viewController)
{
    
}

HeatingZoneListener::~HeatingZoneListener()
{
    
}

void HeatingZoneListener::UpdateNumberOfHeatingZones(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got NumberOfHeatingZones: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.numberOfHeatingZonesCell.value.text = valueAsStr;
    });
}

void HeatingZoneListener::OnResponseGetNumberOfHeatingZones(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateNumberOfHeatingZones(value);
}

void HeatingZoneListener::OnNumberOfHeatingZonesChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateNumberOfHeatingZones(value);
}


void HeatingZoneListener::UpdateMaxHeatingLevels(const std::vector<uint8_t>& value)
{
    NSString *valueArrayAsString = @"";
    std::vector<uint8_t>::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%u,", *it]];
        ++it;
    }
    NSLog(@"Got MaxHeatingLevels: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxHeatingLevelsCell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
}

void HeatingZoneListener::OnResponseGetMaxHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateMaxHeatingLevels(value);
}

void HeatingZoneListener::OnMaxHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
{
    UpdateMaxHeatingLevels(value);
}


void HeatingZoneListener::UpdateHeatingLevels(const std::vector<uint8_t>& value)
{
    NSString *valueArrayAsString = @"";
    std::vector<uint8_t>::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%u,", *it]];
        ++it;
    }
    NSLog(@"Got HeatingLevels: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.heatingLevelsCell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
}

void HeatingZoneListener::OnResponseGetHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateHeatingLevels(value);
}

void HeatingZoneListener::OnHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
{
    UpdateHeatingLevels(value);
}


