////////////////////////////////////////////////////////////////////////////////
//    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//    PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "ColorListener.h"
#import "ColorViewController.h"
#import "CDMUtil.h"

ColorListener::ColorListener(ColorViewController *viewController):viewController(viewController)
{
    
}

ColorListener::~ColorListener()
{
    
}

void ColorListener::UpdateHue(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got Hue: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.hueCell.value.text = valueAsStr;
    });
}

void ColorListener::OnResponseGetHue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateHue(value);
}

void ColorListener::OnHueChanged(const qcc::String& objectPath, const double value)
{
    UpdateHue(value);
}

void ColorListener::OnResponseSetHue(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetHue: succeeded");
    }else {
        NSLog(@"SetHue: failed");
    }
}

void ColorListener::UpdateSaturation(const double value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%f", value];
    NSLog(@"Got Saturation: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.saturationCell.value.text = valueAsStr;
    });
}

void ColorListener::OnResponseGetSaturation(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    UpdateSaturation(value);
}

void ColorListener::OnSaturationChanged(const qcc::String& objectPath, const double value)
{
    UpdateSaturation(value);
}

void ColorListener::OnResponseSetSaturation(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetSaturation: succeeded");
    }else {
        NSLog(@"SetSaturation: failed");
    }
}
