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

#ifndef HeatingZoneListener_h
#define HeatingZoneListener_h

#import "HeatingZoneViewController.h"
#import "alljoyn/cdm/interfaces/operation/HeatingZoneInterface.h"
#import "alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllerListener.h"

class HeatingZoneListener : public ajn::services::HeatingZoneIntfControllerListener
{
    public:
        HeatingZoneListener(HeatingZoneViewController *viewController);
    
        virtual ~HeatingZoneListener();

        virtual void UpdateNumberOfHeatingZones(const uint8_t value);
        virtual void OnResponseGetNumberOfHeatingZones(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnNumberOfHeatingZonesChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateMaxHeatingLevels(const std::vector<uint8_t>& value);
        virtual void OnResponseGetMaxHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);
        virtual void OnMaxHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value);

        virtual void UpdateHeatingLevels(const std::vector<uint8_t>& value);
        virtual void OnResponseGetHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);
        virtual void OnHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value);

        

    private:
        HeatingZoneViewController *viewController;
};

#endif /* HeatingZoneListener_h */