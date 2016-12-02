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

#ifndef LanguageDisplayListener_h
#define LanguageDisplayListener_h

#import "LanguageDisplayViewController.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayInterface.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControllerListener.h"

class LanguageDisplayListener : public ajn::services::LanguageDisplayIntfControllerListener
{
    public:
        LanguageDisplayListener(LanguageDisplayViewController *viewController);
    
        virtual ~LanguageDisplayListener();

        virtual void UpdateDisplayLanguage(const qcc::String& value);
        virtual void OnResponseGetDisplayLanguage(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context);
        virtual void OnDisplayLanguageChanged(const qcc::String& objectPath, const qcc::String& value);
        virtual void OnResponseSetDisplayLanguage(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateSupportedDisplayLanguages(const std::vector<qcc::String>& value);
        virtual void OnResponseGetSupportedDisplayLanguages(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& value, void* context);

        

    private:
        LanguageDisplayViewController *viewController;
};

#endif /* LanguageDisplayListener_h */
