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

#import "FanSpeedLevelListener.h"
#import "FanSpeedLevelViewController.h"
#import "CDMUtil.h"

FanSpeedLevelListener::FanSpeedLevelListener(FanSpeedLevelViewController *viewController):viewController(viewController)
{
    
}

FanSpeedLevelListener::~FanSpeedLevelListener()
{
    
}

void FanSpeedLevelListener::UpdateFanSpeedLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got FanSpeedLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.fanSpeedLevelCell.value.text = valueAsStr;
    });
}

void FanSpeedLevelListener::OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateFanSpeedLevel(value);
}

void FanSpeedLevelListener::OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateFanSpeedLevel(value);
}

void FanSpeedLevelListener::OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetFanSpeedLevel: succeeded");
    }else {
        NSLog(@"SetFanSpeedLevel: failed");
    }
}

void FanSpeedLevelListener::UpdateMaxFanSpeedLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxFanSpeedLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxFanSpeedLevelCell.value.text = valueAsStr;
    });
}

void FanSpeedLevelListener::OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxFanSpeedLevel(value);
}



void FanSpeedLevelListener::UpdateAutoMode(const AutoMode value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got AutoMode: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.autoModeCell.value.text = valueAsStr;
    });
}

void FanSpeedLevelListener::OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context)
{
    UpdateAutoMode(value);
}

void FanSpeedLevelListener::OnAutoModeChanged(const qcc::String& objectPath, const AutoMode value)
{
    UpdateAutoMode(value);
}

void FanSpeedLevelListener::OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetAutoMode: succeeded");
    }else {
        NSLog(@"SetAutoMode: failed");
    }
}
