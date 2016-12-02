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

#import "CurrentPowerListener.h"
#import "CurrentPowerViewController.h"
#import "CDMUtil.h"

CurrentPowerListener::CurrentPowerListener(CurrentPowerViewController *viewController):viewController(viewController)
{
    
}

CurrentPowerListener::~CurrentPowerListener()
{
    
}

void CurrentPowerListener::UpdateCurrentPower(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got CurrentPower: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.currentPowerCell.value.text = valueAsStr;
    });
}

void CurrentPowerListener::OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateCurrentPower(value);
}

void CurrentPowerListener::OnCurrentPowerChanged(const qcc::String& objectPath, const double value)
{
    UpdateCurrentPower(value);
}


void CurrentPowerListener::UpdatePrecision(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got Precision: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.precisionCell.value.text = valueAsStr;
    });
}

void CurrentPowerListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdatePrecision(value);
}

void CurrentPowerListener::OnPrecisionChanged(const qcc::String& objectPath, const double value)
{
    UpdatePrecision(value);
}


void CurrentPowerListener::UpdateUpdateMinTime(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got UpdateMinTime: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.updateMinTimeCell.value.text = valueAsStr;
    });
}

void CurrentPowerListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateUpdateMinTime(value);
}

void CurrentPowerListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateUpdateMinTime(value);
}

