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

#import "ClimateControlModeListener.h"
#import "ClimateControlModeViewController.h"
#import "CDMUtil.h"

ClimateControlModeListener::ClimateControlModeListener(ClimateControlModeViewController *viewController):viewController(viewController)
{
    
}

ClimateControlModeListener::~ClimateControlModeListener()
{
    
}

void ClimateControlModeListener::UpdateMode(const Mode value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got Mode: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.modeCell.value.text = valueAsStr;
    });
}

void ClimateControlModeListener::OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context)
{
    UpdateMode(value);
}

void ClimateControlModeListener::OnModeChanged(const qcc::String& objectPath, const Mode value)
{
    UpdateMode(value);
}

void ClimateControlModeListener::OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetMode: succeeded");
    }else {
        NSLog(@"SetMode: failed");
    }
}

void ClimateControlModeListener::UpdateSupportedModes(const std::vector<Mode>& value)
{
    [viewController setSupportedModes:value];
}

void ClimateControlModeListener::OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context)
{
    UpdateSupportedModes(value);
}

void ClimateControlModeListener::OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value)
{
    UpdateSupportedModes(value);
}


void ClimateControlModeListener::UpdateOperationalState(const OperationalState value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%hu", value];
    NSLog(@"Got OperationalState: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.operationalStateCell.value.text = valueAsStr;
    });
}

void ClimateControlModeListener::OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context)
{
    UpdateOperationalState(value);
}

void ClimateControlModeListener::OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value)
{
    UpdateOperationalState(value);
}


