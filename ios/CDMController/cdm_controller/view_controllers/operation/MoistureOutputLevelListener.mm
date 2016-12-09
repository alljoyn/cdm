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

#import "MoistureOutputLevelListener.h"
#import "MoistureOutputLevelViewController.h"
#import "CDMUtil.h"

MoistureOutputLevelListener::MoistureOutputLevelListener(MoistureOutputLevelViewController *viewController):viewController(viewController)
{
    
}

MoistureOutputLevelListener::~MoistureOutputLevelListener()
{
    
}

void MoistureOutputLevelListener::UpdateMoistureOutputLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MoistureOutputLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.moistureOutputLevelCell.value.text = valueAsStr;
    });
}

void MoistureOutputLevelListener::OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMoistureOutputLevel(value);
}

void MoistureOutputLevelListener::OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMoistureOutputLevel(value);
}

void MoistureOutputLevelListener::OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetMoistureOutputLevel: succeeded");
    }else {
        NSLog(@"SetMoistureOutputLevel: failed");
    }
}

void MoistureOutputLevelListener::UpdateMaxMoistureOutputLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxMoistureOutputLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxMoistureOutputLevelCell.value.text = valueAsStr;
    });
}

void MoistureOutputLevelListener::OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxMoistureOutputLevel(value);
}

void MoistureOutputLevelListener::OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMaxMoistureOutputLevel(value);
}


void MoistureOutputLevelListener::UpdateAutoMode(const AutoMode value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got AutoMode: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.autoModeCell.value.text = valueAsStr;
    });
}

void MoistureOutputLevelListener::OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context)
{
    UpdateAutoMode(value);
}

void MoistureOutputLevelListener::OnAutoModeChanged(const qcc::String& objectPath, const AutoMode value)
{
    UpdateAutoMode(value);
}

void MoistureOutputLevelListener::OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetAutoMode: succeeded");
    }else {
        NSLog(@"SetAutoMode: failed");
    }
}
