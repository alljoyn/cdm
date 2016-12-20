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

#import "EnergyUsageListener.h"
#import "EnergyUsageViewController.h"
#import "CDMUtil.h"

EnergyUsageListener::EnergyUsageListener(EnergyUsageViewController *viewController):viewController(viewController)
{
    
}

EnergyUsageListener::~EnergyUsageListener()
{
    
}

void EnergyUsageListener::UpdateCumulativeEnergy(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got CumulativeEnergy: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.cumulativeEnergyCell.value.text = valueAsStr;
    });
}

void EnergyUsageListener::OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateCumulativeEnergy(value);
}

void EnergyUsageListener::OnCumulativeEnergyChanged(const qcc::String& objectPath, const double value)
{
    UpdateCumulativeEnergy(value);
}


void EnergyUsageListener::UpdatePrecision(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got Precision: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.precisionCell.value.text = valueAsStr;
    });
}

void EnergyUsageListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdatePrecision(value);
}

void EnergyUsageListener::OnPrecisionChanged(const qcc::String& objectPath, const double value)
{
    UpdatePrecision(value);
}


void EnergyUsageListener::UpdateUpdateMinTime(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got UpdateMinTime: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.updateMinTimeCell.value.text = valueAsStr;
    });
}

void EnergyUsageListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateUpdateMinTime(value);
}

void EnergyUsageListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateUpdateMinTime(value);
}


void EnergyUsageListener::OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"ResetCumulativeEnergy succeeded");
    } else {
        NSLog(@"ResetCumulativeEnergy failed");
    }
}
