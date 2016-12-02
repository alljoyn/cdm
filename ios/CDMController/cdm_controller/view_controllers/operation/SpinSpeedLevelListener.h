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

#ifndef SpinSpeedLevelListener_h
#define SpinSpeedLevelListener_h

#import "SpinSpeedLevelViewController.h"
#import "alljoyn/cdm/interfaces/operation/SpinSpeedLevelInterface.h"
#import "alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllerListener.h"

class SpinSpeedLevelListener : public ajn::services::SpinSpeedLevelIntfControllerListener
{
    public:
        SpinSpeedLevelListener(SpinSpeedLevelViewController *viewController);
    
        virtual ~SpinSpeedLevelListener();

        virtual void UpdateMaxLevel(const uint8_t value);
        virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);

        virtual void UpdateTargetLevel(const uint8_t value);
        virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSelectableLevels(const std::vector<uint8_t>& value);
        virtual void OnResponseGetSelectableLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);
        virtual void OnSelectableLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value);

        

    private:
        SpinSpeedLevelViewController *viewController;
};

#endif /* SpinSpeedLevelListener_h */