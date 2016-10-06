/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "AudioVolumeListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus AudioVolumeListener::OnSetVolume(const uint8_t& volume)
{
    cout << "AudioVolumeListener::OnSetVolume() - volume : " << (int)volume << endl;
    return ER_OK;
}

QStatus AudioVolumeListener::OnGetVolume(uint8_t& volume)
{
    cout << "AudioVolumeListener::OnGetVolume()" << endl;
    return ER_OK;
}

QStatus AudioVolumeListener::OnSetMute(const bool& mute)
{
    cout << "AudioVolumeListener::OnSetMute() - mute : " << mute << endl;
    return ER_OK;
}

QStatus AudioVolumeListener::OnGetMute(bool& mute)
{
    cout << "AudioVolumeListener::OnGetMute()" << endl;
    return ER_OK;
}

QStatus AudioVolumeListener::OnGetMaxVolume(uint8_t& maxVolume)
{
    cout << "AudioVolumeListener::OnGetMaxVolume()" << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* AudioVolumeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new AudioVolumeCommands(sample, objectPath);
}

AudioVolumeCommands::AudioVolumeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

AudioVolumeCommands::~AudioVolumeCommands()
{
}

void AudioVolumeCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(AUDIO_VOLUME_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<AudioVolumeIntfControllee*>(cdmInterface);

        RegisterCommand(&AudioVolumeCommands::OnCmdGetVolume, "gv", "get volume");
        RegisterCommand(&AudioVolumeCommands::OnCmdSetVolume, "sv", "set volume (use 'sv <volume>'");
        RegisterCommand(&AudioVolumeCommands::OnCmdGetMaxVolume, "gmv", "get max volume");
        RegisterCommand(&AudioVolumeCommands::OnCmdSetMaxVolume, "smv", "set max volume (use 'smv <max volume>'");
        RegisterCommand(&AudioVolumeCommands::OnCmdGetMute, "gmute", "get mute");
        RegisterCommand(&AudioVolumeCommands::OnCmdSetMute, "smute", "set mute (use 'smute <0/1>'");

        return;
    } else {
        PrintCommands();
    }
}

void AudioVolumeCommands::OnCmdGetVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfControllee* intfControllee = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetVolume() << endl;
}

void AudioVolumeCommands::OnCmdSetVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfControllee* intfControllee = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int volume = strtol(cmd.c_str(), NULL, 10);
    if (volume < 0 || volume >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetVolume((uint8_t)volume);
}

void AudioVolumeCommands::OnCmdGetMute(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfControllee* intfControllee = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetMute() << endl;
}

void AudioVolumeCommands::OnCmdSetMute(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfControllee* intfControllee = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mute = strtol(cmd.c_str(), NULL, 10);
    if (mute == 0 || mute == 1) {
        intfControllee->SetMute(mute);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}

void AudioVolumeCommands::OnCmdGetMaxVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfControllee* intfControllee = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMaxVolume() << endl;
}

void AudioVolumeCommands::OnCmdSetMaxVolume(Commands* commands, std::string& cmd)
{
    AudioVolumeIntfControllee* intfControllee = static_cast<AudioVolumeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int maxVolume = strtol(cmd.c_str(), NULL, 10);
    if (maxVolume < 0 || maxVolume >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetMaxVolume((uint8_t)maxVolume);
}