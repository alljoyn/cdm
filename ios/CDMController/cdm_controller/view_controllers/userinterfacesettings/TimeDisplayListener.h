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

#ifndef TimeDisplayListener_h
#define TimeDisplayListener_h

#import "TimeDisplayViewController.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControllerListener.h"

class TimeDisplayListener : public ajn::services::TimeDisplayIntfControllerListener
{
    public:
        TimeDisplayListener(TimeDisplayViewController *viewController);
    
        virtual ~TimeDisplayListener();

        virtual void UpdateDisplayTimeFormat(const uint8_t value);
        virtual void OnResponseGetDisplayTimeFormat(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnDisplayTimeFormatChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetDisplayTimeFormat(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSupportedDisplayTimeFormats(const std::vector<uint8_t>& value);
        virtual void OnResponseGetSupportedDisplayTimeFormats(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context);

        

    private:
        TimeDisplayViewController *viewController;
};

#endif /* TimeDisplayListener_h */
