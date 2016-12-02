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

#ifndef BrightnessListener_h
#define BrightnessListener_h

#import "BrightnessViewController.h"
#import "alljoyn/cdm/interfaces/operation/BrightnessInterface.h"
#import "alljoyn/cdm/interfaces/operation/BrightnessIntfControllerListener.h"

class BrightnessListener : public ajn::services::BrightnessIntfControllerListener
{
    public:
        BrightnessListener(BrightnessViewController *viewController);
    
        virtual ~BrightnessListener();

        virtual void UpdateBrightness(const double value);
        virtual void OnResponseGetBrightness(QStatus status, const qcc::String& objectPath, const double value, void* context);
        virtual void OnBrightnessChanged(const qcc::String& objectPath, const double value);
        virtual void OnResponseSetBrightness(QStatus status, const qcc::String& objectPath, void* context);

        

    private:
        BrightnessViewController *viewController;
};

#endif /* BrightnessListener_h */
