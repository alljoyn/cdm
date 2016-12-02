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

#ifndef CurrentHumidityListener_h
#define CurrentHumidityListener_h

#import "CurrentHumidityViewController.h"
#import "alljoyn/cdm/interfaces/environment/CurrentHumidityInterface.h"
#import "alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControllerListener.h"

class CurrentHumidityListener : public ajn::services::CurrentHumidityIntfControllerListener
{
    public:
        CurrentHumidityListener(CurrentHumidityViewController *viewController);
    
        virtual ~CurrentHumidityListener();

        virtual void UpdateCurrentValue(const uint8_t value);
        virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateMaxValue(const uint8_t value);
        virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value);

        

    private:
        CurrentHumidityViewController *viewController;
};

#endif /* CurrentHumidityListener_h */
