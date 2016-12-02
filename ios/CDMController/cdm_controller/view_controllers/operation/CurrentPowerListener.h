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

#ifndef CurrentPowerListener_h
#define CurrentPowerListener_h

#import "CurrentPowerViewController.h"
#import "alljoyn/cdm/interfaces/operation/CurrentPowerInterface.h"
#import "alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllerListener.h"

class CurrentPowerListener : public ajn::services::CurrentPowerIntfControllerListener
{
    public:
        CurrentPowerListener(CurrentPowerViewController *viewController);
    
        virtual ~CurrentPowerListener();

        virtual void UpdateCurrentPower(const double value);
        virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double value);

        virtual void UpdatePrecision(const double value);
        virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value);

        virtual void UpdateUpdateMinTime(const uint16_t value);
        virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
        virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value);

        

    private:
        CurrentPowerViewController *viewController;
};

#endif /* CurrentPowerListener_h */