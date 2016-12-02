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

#ifndef TemperatureDisplayListener_h
#define TemperatureDisplayListener_h

#import "TemperatureDisplayViewController.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllerListener.h"

class TemperatureDisplayListener : public ajn::services::TemperatureDisplayIntfControllerListener
{
    public:
        TemperatureDisplayListener(TemperatureDisplayViewController *viewController);
    
        virtual ~TemperatureDisplayListener();

        virtual void UpdateDisplayTemperatureUnit(const uint8_t value);
        virtual void OnResponseGetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnDisplayTemperatureUnitChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSupportedDisplayTemperatureUnits(const std::vector<uint8_t>& value);
        virtual void OnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);

        

    private:
        TemperatureDisplayViewController *viewController;
};

#endif /* TemperatureDisplayListener_h */
