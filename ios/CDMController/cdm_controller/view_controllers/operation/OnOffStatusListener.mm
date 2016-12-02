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

#import "OnOffStatusListener.h"
#import "OnOffStatusViewController.h"
#import "CDMUtil.h"

OnOffStatusListener::OnOffStatusListener(OnOffStatusViewController *viewController):viewController(viewController)
{
    
}

OnOffStatusListener::~OnOffStatusListener()
{
    
}

void OnOffStatusListener::UpdateIsOn(const bool value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%@", [CDMUtil boolToNSString:value]];
    NSLog(@"Got IsOn: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.isOnCell.value.text = valueAsStr;
    });
}

void OnOffStatusListener::OnResponseGetIsOn(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    UpdateIsOn(value);
}

void OnOffStatusListener::OnIsOnChanged(const qcc::String& objectPath, const bool value)
{
    UpdateIsOn(value);
}


