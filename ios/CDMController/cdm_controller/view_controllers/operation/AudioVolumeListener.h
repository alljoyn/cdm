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

#ifndef AudioVolumeListener_h
#define AudioVolumeListener_h

#import "AudioVolumeViewController.h"
#import "alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h"
#import "alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllerListener.h"

class AudioVolumeListener : public ajn::services::AudioVolumeIntfControllerListener
{
    public:
        AudioVolumeListener(AudioVolumeViewController *viewController);
    
        virtual ~AudioVolumeListener();

        virtual void UpdateVolume(const uint8_t value);
        virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnVolumeChanged(const qcc::String& objectPath, const uint8_t value);
        virtual void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context);

        virtual void UpdateMaxVolume(const uint8_t value);
        virtual void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
        virtual void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t value);

        virtual void UpdateMute(const bool value);
        virtual void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool value, void* context);
        virtual void OnMuteChanged(const qcc::String& objectPath, const bool value);
        virtual void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context);

        

    private:
        AudioVolumeViewController *viewController;
};

#endif /* AudioVolumeListener_h */
