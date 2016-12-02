////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for any
//    purpose with or without fee is hereby granted, provided that the above
//    copyright notice and this permission notice appear in all copies.
//
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "TargetTemperatureListener.h"
#import "TargetTemperatureViewController.h"
#import "CDMUtil.h"

TargetTemperatureListener::TargetTemperatureListener(TargetTemperatureViewController *viewController):viewController(viewController)
{
    
}

TargetTemperatureListener::~TargetTemperatureListener()
{
    
}

void TargetTemperatureListener::UpdateTargetValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got TargetValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.targetValueCell.value.text = valueAsStr;
    });
}

void TargetTemperatureListener::OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateTargetValue(value);
}

void TargetTemperatureListener::OnTargetValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateTargetValue(value);
}

void TargetTemperatureListener::OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetTargetValue: succeeded");
    }else {
        NSLog(@"SetTargetValue: failed");
    }
}

void TargetTemperatureListener::UpdateMinValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got MinValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.minValueCell.value.text = valueAsStr;
    });
}

void TargetTemperatureListener::OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateMinValue(value);
}

void TargetTemperatureListener::OnMinValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateMinValue(value);
}


void TargetTemperatureListener::UpdateMaxValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got MaxValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxValueCell.value.text = valueAsStr;
    });
}

void TargetTemperatureListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateMaxValue(value);
}

void TargetTemperatureListener::OnMaxValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateMaxValue(value);
}


void TargetTemperatureListener::UpdateStepValue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got StepValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.stepValueCell.value.text = valueAsStr;
    });
}

void TargetTemperatureListener::OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateStepValue(value);
}

void TargetTemperatureListener::OnStepValueChanged(const qcc::String& objectPath, const double value)
{
    UpdateStepValue(value);
}


