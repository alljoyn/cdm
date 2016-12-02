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

#import "TemperatureDisplayListener.h"
#import "TemperatureDisplayViewController.h"
#import "CDMUtil.h"

TemperatureDisplayListener::TemperatureDisplayListener(TemperatureDisplayViewController *viewController):viewController(viewController)
{
    
}

TemperatureDisplayListener::~TemperatureDisplayListener()
{
    
}

void TemperatureDisplayListener::UpdateDisplayTemperatureUnit(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got DisplayTemperatureUnit: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.displayTemperatureUnitCell.value.text = valueAsStr;
    });
}

void TemperatureDisplayListener::OnResponseGetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateDisplayTemperatureUnit(value);
}

void TemperatureDisplayListener::OnDisplayTemperatureUnitChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateDisplayTemperatureUnit(value);
}

void TemperatureDisplayListener::OnResponseSetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetDisplayTemperatureUnit: succeeded");
    }else {
        NSLog(@"SetDisplayTemperatureUnit: failed");
    }
}

void TemperatureDisplayListener::UpdateSupportedDisplayTemperatureUnits(const std::vector<uint8_t>& value)
{
    [viewController setSupportedDisplayTemperatureUnits:value];
}

void TemperatureDisplayListener::OnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateSupportedDisplayTemperatureUnits(value);
}


