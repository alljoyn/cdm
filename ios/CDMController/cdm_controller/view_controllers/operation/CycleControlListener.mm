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

#import "CycleControlListener.h"
#import "CycleControlViewController.h"
#import "CDMUtil.h"

CycleControlListener::CycleControlListener(CycleControlViewController *viewController):viewController(viewController)
{
    
}

CycleControlListener::~CycleControlListener()
{
    
}

void CycleControlListener::UpdateOperationalState(const OperationalState value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got OperationalState: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.operationalStateCell.value.text = valueAsStr;
    });
}

void CycleControlListener::OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context)
{
    UpdateOperationalState(value);
}

void CycleControlListener::OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value)
{
    UpdateOperationalState(value);
}


void CycleControlListener::UpdateSupportedOperationalStates(const std::vector<OperationalState>& value)
{
    [viewController setSupportedOperationalStates:value];
}

void CycleControlListener::OnResponseGetSupportedOperationalStates(QStatus status, const qcc::String& objectPath, const std::vector<OperationalState>& value, void* context)
{
    UpdateSupportedOperationalStates(value);
}



void CycleControlListener::UpdateSupportedOperationalCommands(const std::vector<OperationalCommands>& value)
{
    NSString *valueArrayAsString = @"";
    std::vector<OperationalCommands>::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%u/,", *it]];
        ++it;
    }
    NSLog(@"Got SupportedOperationalCommands: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.supportedOperationalCommandsCell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
}

void CycleControlListener::OnResponseGetSupportedOperationalCommands(QStatus status, const qcc::String& objectPath, const std::vector<OperationalCommands>& value, void* context)
{
    UpdateSupportedOperationalCommands(value);
}



void CycleControlListener::OnResponseExecuteOperationalCommand(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"ExecuteOperationalCommand succeeded");
    } else {
        NSLog(@"ExecuteOperationalCommand failed");
    }
}

