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

#import "BatteryStatusListener.h"
#import "BatteryStatusViewController.h"
#import "CDMUtil.h"

BatteryStatusListener::BatteryStatusListener(BatteryStatusViewController *viewController):viewController(viewController)
{
    
}

BatteryStatusListener::~BatteryStatusListener()
{
    
}

void BatteryStatusListener::UpdateCurrentValue(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got CurrentValue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.currentValueCell.value.text = valueAsStr;
    });
}

void BatteryStatusListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateCurrentValue(value);
}

void BatteryStatusListener::OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateCurrentValue(value);
}


void BatteryStatusListener::UpdateIsCharging(const bool value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%@", [CDMUtil boolToNSString:value]];
    NSLog(@"Got IsCharging: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.isChargingCell.value.text = valueAsStr;
    });
}

void BatteryStatusListener::OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    UpdateIsCharging(value);
}

void BatteryStatusListener::OnIsChargingChanged(const qcc::String& objectPath, const bool value)
{
    UpdateIsCharging(value);
}

