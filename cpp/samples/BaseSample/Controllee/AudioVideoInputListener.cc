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

#include "AudioVideoInputListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus AudioVideoInputListener::OnSetInputSourceId(const uint16_t& inputSourceId)
{
    cout << "AudioVideoInputListener::OnSetInputSourceId() - inputSourceId : " << inputSourceId << endl;
    return ER_OK;
}

QStatus AudioVideoInputListener::OnGetInputSourceId(uint16_t& inputSourceId)
{
    cout << "AudioVideoInputListener::OnGetInputSourceId()" << endl;
    return ER_OK;
}

QStatus AudioVideoInputListener::OnGetSupportedInputSources(AudioVideoInputInterface::InputSources& supportedInputSources)
{
    cout << "AudioVideoInputListener::OnGetSupportedInputSources" << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* AudioVideoInputCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new AudioVideoInputCommands(sample, objectPath);
}

AudioVideoInputCommands::AudioVideoInputCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

AudioVideoInputCommands::~AudioVideoInputCommands()
{
}

void AudioVideoInputCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(AUDIO_VIDEO_INPUT_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<AudioVideoInputIntfControllee*>(cdmInterface);

        RegisterCommand(&AudioVideoInputCommands::OnCmdGetInputSourceId, "gisi", "get input source id");
        RegisterCommand(&AudioVideoInputCommands::OnCmdSetInputSourceId, "sisi", "set input source id (use 'sisi <id>'");
        RegisterCommand(&AudioVideoInputCommands::OnCmdGetSupportedInputSources, "gsis", "get supported input sources");
    } else {
        PrintCommands();
    }
}

void AudioVideoInputCommands::InitializeProperties()
{
    if (m_intfControllee) {
        AudioVideoInputInterface::InputSources supportedInputSources;
        AudioVideoInputInterface::InputSource source1, source2;
        source1.sourceType = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SOURCE_TYPE_TUNER;
        source1.signalPresence = 1;
        source1.portNumber = 1;
        source1.friendlyName = "TV";
        source2.sourceType = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SOURCE_TYPE_HDMI;
        source2.signalPresence = 0;
        source2.portNumber = 1;
        source2.friendlyName = "HDMI_1";
        supportedInputSources[0x8000] = source1;
        supportedInputSources[0x8001] = source2;
        m_intfControllee->SetSupportedInputSources(supportedInputSources);
        m_intfControllee->SetInputSourceId(0x8000);
    }
}

void AudioVideoInputCommands::OnCmdGetInputSourceId(Commands* commands, std::string& cmd)
{
    AudioVideoInputIntfControllee* intfControllee = static_cast<AudioVideoInputCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetInputSourceId() << endl;
}

void AudioVideoInputCommands::OnCmdSetInputSourceId(Commands* commands, std::string& cmd)
{
    AudioVideoInputIntfControllee* intfControllee = static_cast<AudioVideoInputCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int inputSourceId = strtol(cmd.c_str(), NULL, 10);
    if (inputSourceId < 0 || inputSourceId >= 65536) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetInputSourceId((uint16_t)inputSourceId);
}

void AudioVideoInputCommands::OnCmdGetSupportedInputSources(Commands* commands, std::string& cmd)
{
    AudioVideoInputIntfControllee* intfControllee = static_cast<AudioVideoInputCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const AudioVideoInputInterface::InputSources& supportedInputSources = intfControllee->GetSupportedInputSources();
    for(AudioVideoInputInterface::InputSources::const_iterator citr = supportedInputSources.begin();
        citr != supportedInputSources.end(); citr++) {
        cout << "id : " << citr->first << " "
             << "source type : " << citr->second.sourceType << " "
             << "signal presence : " << (int)citr->second.signalPresence << " "
             << "port number : " << citr->second.portNumber << " "
             << "friendly name : " << citr->second.friendlyName.c_str() << " " << endl;
    }
}