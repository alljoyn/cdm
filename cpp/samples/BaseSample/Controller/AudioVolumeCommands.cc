/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "AudioVolumeCommands.h"
#include "ControllerSample.h"

AudioVolumeListener::AudioVolumeListener()
{
}

AudioVolumeListener::~AudioVolumeListener()
{
}

void AudioVolumeListener::OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void AudioVolumeListener::OnResponseGetVolume(QStatus status, const qcc::String& objectPath, uint8_t volume, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "volume: " << (int)volume << endl;
}

void AudioVolumeListener::OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t maxVolume, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "max volume: " << (int)maxVolume << endl;
}

void AudioVolumeListener::OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void AudioVolumeListener::OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool mute, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "mute: " << mute << endl;
}

void AudioVolumeListener::OnVolumeChanged(const qcc::String& objectPath, const uint8_t volume)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "volume: " << (int)volume << endl;
}

void AudioVolumeListener::OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t maxVolume)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "max volume: " << (int)maxVolume << endl;
}

void AudioVolumeListener::OnMuteChanged(const qcc::String& objectPath, const bool mute)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "mute: " << mute << endl;
}

AudioVolumeCommands::AudioVolumeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

AudioVolumeCommands::~AudioVolumeCommands()
{

}

void AudioVolumeCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(AUDIO_VOLUME_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<AudioVolumeIntfController*>(cdmInterface);
    }

    RegisterCommand(&AudioVolumeCommands::OnCmdGetVolume, "gv", "get volume");
    RegisterCommand(&AudioVolumeCommands::OnCmdSetVolume, "sv", "set volume (use 'sv <volume>'");
    RegisterCommand(&AudioVolumeCommands::OnCmdGetMaxVolume, "gmv", "get max volume");
    RegisterCommand(&AudioVolumeCommands::OnCmdGetMute, "gmute", "get mute");
    RegisterCommand(&AudioVolumeCommands::OnCmdSetMute, "smute", "set mute (use 'smute <0/1>'");
    PrintCommands();
}

void AudioVolumeCommands::OnCmdGetVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfController* intfController = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetVolume();
}

void AudioVolumeCommands::OnCmdSetVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfController* intfController = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int volume = strtol(cmd.c_str(), NULL, 10);
    if (volume < 0 || volume >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetVolume((uint8_t)volume);
}

void AudioVolumeCommands::OnCmdGetMaxVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfController* intfController = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxVolume();
}

void AudioVolumeCommands::OnCmdGetMute(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfController* intfController = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMute();
}

void AudioVolumeCommands::OnCmdSetMute(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfController* intfController = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mute = strtol(cmd.c_str(), NULL, 10);
    if (mute == 0|| mute == 1) {
        intfController->SetMute(mute);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}