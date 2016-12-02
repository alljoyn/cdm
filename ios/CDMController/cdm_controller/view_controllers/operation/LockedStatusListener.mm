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

#import "LockedStatusListener.h"
#import "LockedStatusViewController.h"
#import "CDMUtil.h"

LockedStatusListener::LockedStatusListener(LockedStatusViewController *viewController):viewController(viewController)
{
    
}

LockedStatusListener::~LockedStatusListener()
{
    
}

void LockedStatusListener::UpdateIsLocked(const bool value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%@", [CDMUtil boolToNSString:value]];
    NSLog(@"Got IsLocked: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.isLockedCell.value.text = valueAsStr;
    });
}

void LockedStatusListener::OnResponseGetIsLocked(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    UpdateIsLocked(value);
}

void LockedStatusListener::OnIsLockedChanged(const qcc::String& objectPath, const bool value)
{
    UpdateIsLocked(value);
}


