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

#import "LaundryCyclePhaseListener.h"
#import "LaundryCyclePhaseViewController.h"
#import "CDMUtil.h"

LaundryCyclePhaseListener::LaundryCyclePhaseListener(LaundryCyclePhaseViewController *viewController):viewController(viewController)
{
    
}

LaundryCyclePhaseListener::~LaundryCyclePhaseListener()
{
    
}

void LaundryCyclePhaseListener::UpdateCyclePhase(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got CyclePhase: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.cyclePhaseCell.value.text = valueAsStr;
    });
}

void LaundryCyclePhaseListener::OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateCyclePhase(value);
}

void LaundryCyclePhaseListener::OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateCyclePhase(value);
}


void LaundryCyclePhaseListener::UpdateSupportedCyclePhases(const std::vector<uint8_t>& value)
{
    [viewController setSupportedCyclePhases:value];
}

void LaundryCyclePhaseListener::OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
{
    UpdateSupportedCyclePhases(value);
}

void LaundryCyclePhaseListener::OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
{
    UpdateSupportedCyclePhases(value);
}


void LaundryCyclePhaseListener::OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const std::vector<CyclePhaseDescriptor>& phasesDescription, void* context, const char* errorName, const char* errorMessage)
{
    if(status == ER_OK) {
        NSLog(@"GetVendorPhasesDescription succeeded");
        NSString *builtArgResponseStr = @"";
        std::vector<CyclePhaseDescriptor>::const_iterator it;
        for(it = phasesDescription.begin(); it != phasesDescription.end(); ++it) {
            NSString *line = [NSString stringWithFormat:@"Phase:%u, Name:%s, Description:%s", it->phase, it->name.c_str(), it->description.c_str()];
            builtArgResponseStr = [builtArgResponseStr stringByAppendingString:line];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            viewController.getVendorPhasesDescriptionOutputCell.output.text = builtArgResponseStr;
        });
    } else {
        NSLog(@"GetChannelList failed");
    }
}
