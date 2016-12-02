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

#import "RapidModeTimedListener.h"
#import "RapidModeTimedViewController.h"
#import "CDMUtil.h"

RapidModeTimedListener::RapidModeTimedListener(RapidModeTimedViewController *viewController):viewController(viewController)
{
    
}

RapidModeTimedListener::~RapidModeTimedListener()
{
    
}

void RapidModeTimedListener::UpdateRapidModeMinutesRemaining(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got RapidModeMinutesRemaining: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.rapidModeMinutesRemainingCell.value.text = valueAsStr;
    });
}

void RapidModeTimedListener::OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateRapidModeMinutesRemaining(value);
}

void RapidModeTimedListener::OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateRapidModeMinutesRemaining(value);
}

void RapidModeTimedListener::OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetRapidModeMinutesRemaining: succeeded");
    }else {
        NSLog(@"SetRapidModeMinutesRemaining: failed");
    }
}

void RapidModeTimedListener::UpdateMaxSetMinutes(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got MaxSetMinutes: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxSetMinutesCell.value.text = valueAsStr;
    });
}

void RapidModeTimedListener::OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateMaxSetMinutes(value);
}


