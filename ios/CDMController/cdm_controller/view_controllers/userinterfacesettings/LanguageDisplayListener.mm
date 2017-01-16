////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
// 
//    SPDX-License-Identifier: Apache-2.0
// 
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
// 
//    Copyright 2016 Open Connectivity Foundation and Contributors to
//    AllSeen Alliance. All rights reserved.
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

#import "LanguageDisplayListener.h"
#import "LanguageDisplayViewController.h"
#import "CDMUtil.h"

LanguageDisplayListener::LanguageDisplayListener(LanguageDisplayViewController *viewController):viewController(viewController)
{
    
}

LanguageDisplayListener::~LanguageDisplayListener()
{
    
}

void LanguageDisplayListener::UpdateDisplayLanguage(const qcc::String& value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%s", value.c_str()];
    NSLog(@"Got DisplayLanguage: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.displayLanguageCell.value.text = valueAsStr;
    });
}

void LanguageDisplayListener::OnResponseGetDisplayLanguage(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
{
    UpdateDisplayLanguage(value);
}

void LanguageDisplayListener::OnDisplayLanguageChanged(const qcc::String& objectPath, const qcc::String& value)
{
    UpdateDisplayLanguage(value);
}

void LanguageDisplayListener::OnResponseSetDisplayLanguage(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetDisplayLanguage: succeeded");
    }else {
        NSLog(@"SetDisplayLanguage: failed");
    }
}

void LanguageDisplayListener::UpdateSupportedDisplayLanguages(const std::vector<qcc::String>& value)
{
    [viewController setSupportedDisplayLanguages:value];
}

void LanguageDisplayListener::OnResponseGetSupportedDisplayLanguages(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& value, void* context)
{
    UpdateSupportedDisplayLanguages(value);
}



