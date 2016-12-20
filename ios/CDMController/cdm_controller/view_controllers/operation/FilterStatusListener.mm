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

#import "FilterStatusListener.h"
#import "FilterStatusViewController.h"
#import "CDMUtil.h"

FilterStatusListener::FilterStatusListener(FilterStatusViewController *viewController):viewController(viewController)
{
    
}

FilterStatusListener::~FilterStatusListener()
{
    
}

void FilterStatusListener::UpdateExpectedLifeInDays(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got ExpectedLifeInDays: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.expectedLifeInDaysCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateExpectedLifeInDays(value);
}

void FilterStatusListener::OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateExpectedLifeInDays(value);
}


void FilterStatusListener::UpdateIsCleanable(const bool value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%@", [CDMUtil boolToNSString:value]];
    NSLog(@"Got IsCleanable: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.isCleanableCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    UpdateIsCleanable(value);
}

void FilterStatusListener::OnIsCleanableChanged(const qcc::String& objectPath, const bool value)
{
    UpdateIsCleanable(value);
}


void FilterStatusListener::UpdateOrderPercentage(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got OrderPercentage: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.orderPercentageCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateOrderPercentage(value);
}

void FilterStatusListener::OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateOrderPercentage(value);
}


void FilterStatusListener::UpdateManufacturer(const qcc::String& value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%s", value.c_str()];
    NSLog(@"Got Manufacturer: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.manufacturerCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
{
    UpdateManufacturer(value);
}



void FilterStatusListener::UpdatePartNumber(const qcc::String& value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%s", value.c_str()];
    NSLog(@"Got PartNumber: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.partNumberCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
{
    UpdatePartNumber(value);
}



void FilterStatusListener::UpdateUrl(const qcc::String& value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%s", value.c_str()];
    NSLog(@"Got Url: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.urlCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
{
    UpdateUrl(value);
}



void FilterStatusListener::UpdateLifeRemaining(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got LifeRemaining: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.lifeRemainingCell.value.text = valueAsStr;
    });
}

void FilterStatusListener::OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateLifeRemaining(value);
}

void FilterStatusListener::OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateLifeRemaining(value);
}

