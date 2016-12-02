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

#ifndef CycleControlListener_h
#define CycleControlListener_h

#import "CycleControlViewController.h"
#import "alljoyn/cdm/interfaces/operation/CycleControlInterface.h"
#import "alljoyn/cdm/interfaces/operation/CycleControlIntfControllerListener.h"

class CycleControlListener : public ajn::services::CycleControlIntfControllerListener
{
    public:
        CycleControlListener(CycleControlViewController *viewController);
    
        virtual ~CycleControlListener();

        virtual void UpdateOperationalState(const OperationalState value);
        virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context);
        virtual void OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value);

        virtual void UpdateSupportedOperationalStates(const std::vector<OperationalState>& value);
        virtual void OnResponseGetSupportedOperationalStates(QStatus status, const qcc::String& objectPath, const std::vector<OperationalState>& value, void* context);

        virtual void UpdateSupportedOperationalCommands(const std::vector<OperationalCommands>& value);
        virtual void OnResponseGetSupportedOperationalCommands(QStatus status, const qcc::String& objectPath, const std::vector<OperationalCommands>& value, void* context);

        virtual void OnResponseExecuteOperationalCommand(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
        

    private:
        CycleControlViewController *viewController;
};

#endif /* CycleControlListener_h */
