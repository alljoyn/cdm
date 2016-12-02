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

#ifndef RobotCleaningCyclePhaseListener_h
#define RobotCleaningCyclePhaseListener_h

#import "RobotCleaningCyclePhaseViewController.h"
#import "alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseInterface.h"
#import "alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllerListener.h"

class RobotCleaningCyclePhaseListener : public ajn::services::RobotCleaningCyclePhaseIntfControllerListener
{
    public:
        RobotCleaningCyclePhaseListener(RobotCleaningCyclePhaseViewController *viewController);
    
        virtual ~RobotCleaningCyclePhaseListener();

        virtual void UpdateCyclePhase(const uint8_t value);
        virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateSupportedCyclePhases(const std::vector<uint8_t>& value);
        virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);
        virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value);

        virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const std::vector<CyclePhaseDescriptor>& phasesDescription, void* context, const char* errorName, const char* errorMessage);
        

    private:
        RobotCleaningCyclePhaseViewController *viewController;
};

#endif /* RobotCleaningCyclePhaseListener_h */