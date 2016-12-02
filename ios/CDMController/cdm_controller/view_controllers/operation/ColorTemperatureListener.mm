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

#import "ColorTemperatureListener.h"
#import "ColorTemperatureViewController.h"
#import "CDMUtil.h"

ColorTemperatureListener::ColorTemperatureListener(ColorTemperatureViewController *viewController):viewController(viewController)
{
    
}

ColorTemperatureListener::~ColorTemperatureListener()
{
    
}

void ColorTemperatureListener::UpdateTemperature(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got Temperature: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.temperatureCell.value.text = valueAsStr;
    });
}

void ColorTemperatureListener::OnResponseGetTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateTemperature(value);
}

void ColorTemperatureListener::OnTemperatureChanged(const qcc::String& objectPath, const double value)
{
    UpdateTemperature(value);
}

void ColorTemperatureListener::OnResponseSetTemperature(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetTemperature: succeeded");
    }else {
        NSLog(@"SetTemperature: failed");
    }
}

void ColorTemperatureListener::UpdateMinTemperature(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got MinTemperature: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.minTemperatureCell.value.text = valueAsStr;
    });
}

void ColorTemperatureListener::OnResponseGetMinTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateMinTemperature(value);
}



void ColorTemperatureListener::UpdateMaxTemperature(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got MaxTemperature: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxTemperatureCell.value.text = valueAsStr;
    });
}

void ColorTemperatureListener::OnResponseGetMaxTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateMaxTemperature(value);
}



