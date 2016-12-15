////////////////////////////////////////////////////////////////////////////////
// // Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#import "HvacFanModeListener.h"
#import "HvacFanModeViewController.h"
#import "CDMUtil.h"

HvacFanModeListener::HvacFanModeListener(HvacFanModeViewController *viewController):viewController(viewController)
{
    
}

HvacFanModeListener::~HvacFanModeListener()
{
    
}

void HvacFanModeListener::UpdateMode(const Mode value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got Mode: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.modeCell.value.text = valueAsStr;
    });
}

void HvacFanModeListener::OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context)
{
    UpdateMode(value);
}

void HvacFanModeListener::OnModeChanged(const qcc::String& objectPath, const Mode value)
{
    UpdateMode(value);
}

void HvacFanModeListener::OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetMode: succeeded");
    }else {
        NSLog(@"SetMode: failed");
    }
}

void HvacFanModeListener::UpdateSupportedModes(const std::vector<Mode>& value)
{
    [viewController setSupportedModes:value];
}

void HvacFanModeListener::OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context)
{
    UpdateSupportedModes(value);
}

void HvacFanModeListener::OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value)
{
    UpdateSupportedModes(value);
}

