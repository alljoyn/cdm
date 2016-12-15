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

#import "TargetHumidityListener.h"
#import "TargetHumidityViewController.h"
#import "CDMUtil.h"

TargetHumidityListener::TargetHumidityListener(TargetHumidityViewController *viewController):viewController(viewController)
{
    
}

TargetHumidityListener::~TargetHumidityListener()
{
    
}

void TargetHumidityListener::UpdateTargetValue(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got TargetValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.targetValueCell.value.text = valueAsStr;
    });
}

void TargetHumidityListener::OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateTargetValue(value);
}

void TargetHumidityListener::OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateTargetValue(value);
}

void TargetHumidityListener::OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetTargetValue: succeeded");
    }else {
        NSLog(@"SetTargetValue: failed");
    }
}

void TargetHumidityListener::UpdateMinValue(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MinValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.minValueCell.value.text = valueAsStr;
    });
}

void TargetHumidityListener::OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMinValue(value);
}

void TargetHumidityListener::OnMinValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMinValue(value);
}


void TargetHumidityListener::UpdateMaxValue(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxValueCell.value.text = valueAsStr;
    });
}

void TargetHumidityListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxValue(value);
}

void TargetHumidityListener::OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMaxValue(value);
}


void TargetHumidityListener::UpdateStepValue(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got StepValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.stepValueCell.value.text = valueAsStr;
    });
}

void TargetHumidityListener::OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateStepValue(value);
}

void TargetHumidityListener::OnStepValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateStepValue(value);
}


void TargetHumidityListener::UpdateSelectableHumidityLevels(const std::vector<uint8_t>& value)
{
    NSString *valueArrayAsString = @"";
    std::vector<uint8_t>::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%u,", *it]];
        ++it;
    }
    NSLog(@"Got SelectableHumidityLevels: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.selectableHumidityLevelsCell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
}

void TargetHumidityListener::OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateSelectableHumidityLevels(value);
}

void TargetHumidityListener::OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
{
    UpdateSelectableHumidityLevels(value);
}

