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

#ifndef AirRecirculationModeListener_h
#define AirRecirculationModeListener_h

#import "AirRecirculationModeViewController.h"
#import "alljoyn/cdm/interfaces/operation/AirRecirculationModeInterface.h"
#import "alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllerListener.h"

class AirRecirculationModeListener : public ajn::services::AirRecirculationModeIntfControllerListener
{
    public:
        AirRecirculationModeListener(AirRecirculationModeViewController *viewController);
    
        virtual ~AirRecirculationModeListener();

        virtual void UpdateIsRecirculating(const bool value);
        virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool value, void* context);
        virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool value);
        virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context);

        

    private:
        AirRecirculationModeViewController *viewController;
};

#endif /* AirRecirculationModeListener_h */
