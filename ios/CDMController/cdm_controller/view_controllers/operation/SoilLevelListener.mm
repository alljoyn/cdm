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

#import "SoilLevelListener.h"
#import "SoilLevelViewController.h"
#import "CDMUtil.h"

SoilLevelListener::SoilLevelListener(SoilLevelViewController *viewController):viewController(viewController)
{
    
}

SoilLevelListener::~SoilLevelListener()
{
    
}

void SoilLevelListener::UpdateMaxLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxLevelCell.value.text = valueAsStr;
    });
}

void SoilLevelListener::OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxLevel(value);
}

void SoilLevelListener::OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMaxLevel(value);
}


void SoilLevelListener::UpdateTargetLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got TargetLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.targetLevelCell.value.text = valueAsStr;
    });
}

void SoilLevelListener::OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateTargetLevel(value);
}

void SoilLevelListener::OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateTargetLevel(value);
}

void SoilLevelListener::OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetTargetLevel: succeeded");
    }else {
        NSLog(@"SetTargetLevel: failed");
    }
}

void SoilLevelListener::UpdateSelectableLevels(const std::vector<uint8_t>& value)
{
    [viewController setSelectableLevels:value];
}

void SoilLevelListener::OnResponseGetSelectableLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateSelectableLevels(value);
}

void SoilLevelListener::OnSelectableLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
{
    UpdateSelectableLevels(value);
}


