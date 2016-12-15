////////////////////////////////////////////////////////////////////////////////
// //    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "AudioVolumeListener.h"
#import "AudioVolumeViewController.h"
#import "CDMUtil.h"

AudioVolumeListener::AudioVolumeListener(AudioVolumeViewController *viewController):viewController(viewController)
{
    
}

AudioVolumeListener::~AudioVolumeListener()
{
    
}

void AudioVolumeListener::UpdateVolume(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got Volume: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.volumeCell.value.text = valueAsStr;
    });
}

void AudioVolumeListener::OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateVolume(value);
}

void AudioVolumeListener::OnVolumeChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateVolume(value);
}

void AudioVolumeListener::OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetVolume: succeeded");
    }else {
        NSLog(@"SetVolume: failed");
    }
}

void AudioVolumeListener::UpdateMaxVolume(const uint8_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%u", value];
    NSLog(@"Got MaxVolume: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.maxVolumeCell.value.text = valueAsStr;
    });
}

void AudioVolumeListener::OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    UpdateMaxVolume(value);
}

void AudioVolumeListener::OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t value)
{
    UpdateMaxVolume(value);
}


void AudioVolumeListener::UpdateMute(const bool value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%@", [CDMUtil boolToNSString:value]];
    NSLog(@"Got Mute: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.muteCell.value.text = valueAsStr;
    });
}

void AudioVolumeListener::OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    UpdateMute(value);
}

void AudioVolumeListener::OnMuteChanged(const qcc::String& objectPath, const bool value)
{
    UpdateMute(value);
}

void AudioVolumeListener::OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"SetMute: succeeded");
    }else {
        NSLog(@"SetMute: failed");
    }
}
