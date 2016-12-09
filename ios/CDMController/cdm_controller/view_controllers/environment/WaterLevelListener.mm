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

#import "WaterLevelListener.h"
#import "WaterLevelViewController.h"
#import "CDMUtil.h"

WaterLevelListener::WaterLevelListener(WaterLevelViewController *viewController):viewController(viewController)
{
    
}

WaterLevelListener::~WaterLevelListener()
{
    
}

void WaterLevelListener::UpdateSupplySource(const SupplySource value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got SupplySource: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.supplySourceCell.value.text = valueAsStr;
    });
}

void WaterLevelListener::OnResponseGetSupplySource(QStatus status, const qcc::String& objectPath, const SupplySource value, void* context)
{
    UpdateSupplySource(value);
}

void WaterLevelListener::OnSupplySourceChanged(const qcc::String& objectPath, const SupplySource value)
{
    UpdateSupplySource(value);
}


void WaterLevelListener::UpdateCurrentLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got CurrentLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.currentLevelCell.value.text = valueAsStr;
    });
}

void WaterLevelListener::OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateCurrentLevel(value);
}

void WaterLevelListener::OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateCurrentLevel(value);
}


void WaterLevelListener::UpdateMaxLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxLevelCell.value.text = valueAsStr;
    });
}

void WaterLevelListener::OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxLevel(value);
}

void WaterLevelListener::OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMaxLevel(value);
}

