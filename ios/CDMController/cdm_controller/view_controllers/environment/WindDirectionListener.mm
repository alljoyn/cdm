////////////////////////////////////////////////////////////////////////////////
// //    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "WindDirectionListener.h"
#import "WindDirectionViewController.h"
#import "CDMUtil.h"

WindDirectionListener::WindDirectionListener(WindDirectionViewController *viewController):viewController(viewController)
{
    
}

WindDirectionListener::~WindDirectionListener()
{
    
}

void WindDirectionListener::UpdateHorizontalDirection(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got HorizontalDirection: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.horizontalDirectionCell.value.text = valueAsStr;
    });
}

void WindDirectionListener::OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateHorizontalDirection(value);
}

void WindDirectionListener::OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateHorizontalDirection(value);
}

void WindDirectionListener::OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetHorizontalDirection: succeeded");
    }else {
        NSLog(@"SetHorizontalDirection: failed");
    }
}

void WindDirectionListener::UpdateHorizontalMax(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got HorizontalMax: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.horizontalMaxCell.value.text = valueAsStr;
    });
}

void WindDirectionListener::OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateHorizontalMax(value);
}

void WindDirectionListener::OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateHorizontalMax(value);
}


void WindDirectionListener::UpdateHorizontalAutoMode(const AutoMode value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got HorizontalAutoMode: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.horizontalAutoModeCell.value.text = valueAsStr;
    });
}

void WindDirectionListener::OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context)
{
    UpdateHorizontalAutoMode(value);
}

void WindDirectionListener::OnHorizontalAutoModeChanged(const qcc::String& objectPath, const AutoMode value)
{
    UpdateHorizontalAutoMode(value);
}

void WindDirectionListener::OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetHorizontalAutoMode: succeeded");
    }else {
        NSLog(@"SetHorizontalAutoMode: failed");
    }
}

void WindDirectionListener::UpdateVerticalDirection(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got VerticalDirection: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.verticalDirectionCell.value.text = valueAsStr;
    });
}

void WindDirectionListener::OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateVerticalDirection(value);
}

void WindDirectionListener::OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateVerticalDirection(value);
}

void WindDirectionListener::OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetVerticalDirection: succeeded");
    }else {
        NSLog(@"SetVerticalDirection: failed");
    }
}

void WindDirectionListener::UpdateVerticalMax(const uint16_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got VerticalMax: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.verticalMaxCell.value.text = valueAsStr;
    });
}

void WindDirectionListener::OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    UpdateVerticalMax(value);
}

void WindDirectionListener::OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value)
{
    UpdateVerticalMax(value);
}


void WindDirectionListener::UpdateVerticalAutoMode(const AutoMode value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got VerticalAutoMode: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.verticalAutoModeCell.value.text = valueAsStr;
    });
}

void WindDirectionListener::OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context)
{
    UpdateVerticalAutoMode(value);
}

void WindDirectionListener::OnVerticalAutoModeChanged(const qcc::String& objectPath, const AutoMode value)
{
    UpdateVerticalAutoMode(value);
}

void WindDirectionListener::OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetVerticalAutoMode: succeeded");
    }else {
        NSLog(@"SetVerticalAutoMode: failed");
    }
}
