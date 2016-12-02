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

#ifndef CDMDeviceListener_h
#define CDMDeviceListener_h

#include "DeviceListener.h"
#include "DeviceInfo.h"
#include "CdmAboutData.h"
#include "DeviceViewController.h"
#import "alljoyn/cdm/CdmController.h"

namespace ajn {
namespace services{

class CDMDeviceListener : public ajn::services::DeviceListener
{
    public:
        CDMDeviceListener();
    
        CDMDeviceListener(DeviceViewController *viewController);
    
        virtual ~CDMDeviceListener();
    
    
        virtual void OnDeviceAdded(const char* busname,
                                   SessionPort port,
                                   const CdmAboutData& data,
                                   const AboutObjectDescription& description);
    
        virtual void OnDeviceRemoved(const char* busname);
   
        virtual void OnDeviceSessionJoined(const DeviceInfoPtr& info);
    
        virtual void OnDeviceSessionLost(SessionId sessionId);
    
        void SetController(ajn::services::CdmController *controller);
    
    private:
        DeviceViewController *viewController;
        ajn::services::CdmController *cdmController;
};

}
}
#endif /* CDMDeviceListener_h */
