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

#import "TimeDisplayListener.h"
#import "TimeDisplayViewController.h"
#import "CDMUtil.h"

TimeDisplayListener::TimeDisplayListener(TimeDisplayViewController *viewController):viewController(viewController)
{
    
}

TimeDisplayListener::~TimeDisplayListener()
{
    
}

void TimeDisplayListener::UpdateDisplayTimeFormat(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got DisplayTimeFormat: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.displayTimeFormatCell.value.text = valueAsStr;
    });
}

void TimeDisplayListener::OnResponseGetDisplayTimeFormat(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateDisplayTimeFormat(value);
}

void TimeDisplayListener::OnDisplayTimeFormatChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateDisplayTimeFormat(value);
}

void TimeDisplayListener::OnResponseSetDisplayTimeFormat(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetDisplayTimeFormat: succeeded");
    }else {
        NSLog(@"SetDisplayTimeFormat: failed");
    }
}

void TimeDisplayListener::UpdateSupportedDisplayTimeFormats(const std::vector<uint8_t>& value)
{
    [viewController setSupportedDisplayTimeFormats:value];
}

void TimeDisplayListener::OnResponseGetSupportedDisplayTimeFormats(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateSupportedDisplayTimeFormats(value);
}


