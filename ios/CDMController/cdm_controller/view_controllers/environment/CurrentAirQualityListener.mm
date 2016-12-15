////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#import "CurrentAirQualityListener.h"
#import "CurrentAirQualityViewController.h"
#import "CDMUtil.h"

CurrentAirQualityListener::CurrentAirQualityListener(CurrentAirQualityViewController *viewController):viewController(viewController)
{
    
}

CurrentAirQualityListener::~CurrentAirQualityListener()
{
    
}

void CurrentAirQualityListener::UpdateContaminantType(const ContaminantType value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got ContaminantType: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.contaminantTypeCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityListener::OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context)
{
    UpdateContaminantType(value);
}

void CurrentAirQualityListener::OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value)
{
    UpdateContaminantType(value);
}


void CurrentAirQualityListener::UpdateCurrentValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got CurrentValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.currentValueCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateCurrentValue(value);
}

void CurrentAirQualityListener::OnCurrentValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateCurrentValue(value);
}


void CurrentAirQualityListener::UpdateMinValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got MinValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.minValueCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityListener::OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateMinValue(value);
}

void CurrentAirQualityListener::OnMinValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateMinValue(value);
}


void CurrentAirQualityListener::UpdateMaxValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got MaxValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxValueCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateMaxValue(value);
}

void CurrentAirQualityListener::OnMaxValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateMaxValue(value);
}


void CurrentAirQualityListener::UpdatePrecision(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got Precision: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.precisionCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdatePrecision(value);
}

void CurrentAirQualityListener::OnPrecisionChanged(const qcc::String& objectPath, const double value)
{
    UpdatePrecision(value);
}


void CurrentAirQualityListener::UpdateUpdateMinTime(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got UpdateMinTime: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.updateMinTimeCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateUpdateMinTime(value);
}

void CurrentAirQualityListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateUpdateMinTime(value);
}

