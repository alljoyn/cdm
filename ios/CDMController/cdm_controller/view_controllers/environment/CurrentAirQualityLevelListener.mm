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

#import "CurrentAirQualityLevelListener.h"
#import "CurrentAirQualityLevelViewController.h"
#import "CDMUtil.h"

CurrentAirQualityLevelListener::CurrentAirQualityLevelListener(CurrentAirQualityLevelViewController *viewController):viewController(viewController)
{
    
}

CurrentAirQualityLevelListener::~CurrentAirQualityLevelListener()
{
    
}

void CurrentAirQualityLevelListener::UpdateContaminantType(const ContaminantType value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got ContaminantType: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.contaminantTypeCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityLevelListener::OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context)
{
    UpdateContaminantType(value);
}

void CurrentAirQualityLevelListener::OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value)
{
    UpdateContaminantType(value);
}


void CurrentAirQualityLevelListener::UpdateCurrentLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got CurrentLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.currentLevelCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityLevelListener::OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateCurrentLevel(value);
}

void CurrentAirQualityLevelListener::OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateCurrentLevel(value);
}


void CurrentAirQualityLevelListener::UpdateMaxLevel(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxLevel: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxLevelCell.value.text = valueAsStr;
    });
}

void CurrentAirQualityLevelListener::OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxLevel(value);
}

void CurrentAirQualityLevelListener::OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMaxLevel(value);
}

