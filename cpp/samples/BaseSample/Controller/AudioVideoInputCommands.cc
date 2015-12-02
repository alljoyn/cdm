/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <cstdlib>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>
#include "AudioVideoInputCommands.h"
#include "ControllerSample.h"

AudioVideoInputListener::AudioVideoInputListener()
{
}

AudioVideoInputListener::~AudioVideoInputListener()
{
}

void AudioVideoInputListener::InputSourceIdPropertyChanged(const qcc::String& objectPath, const uint16_t inputSourceId)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "inputSourceId: " << inputSourceId << endl;
}

void AudioVideoInputListener::SupportedInputSourcesPropertyChanged(const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    for(AudioVideoInputInterface::InputSources::const_iterator citer = supportedInputSources.begin();
        citer != supportedInputSources.end(); citer++) {
        cout << citer->first << " "
             << citer->second.sourceType << " "
             << (int)citer->second.signalPresence << " "
             << citer->second.portNumber << " "
             << citer->second.friendlyName.c_str() << " " << endl;
    }
}

void AudioVideoInputListener::GetInputSourceIdPropertyCallback(QStatus status, const qcc::String& objectPath, const uint16_t inputSourceId, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "inputSourceId: " << inputSourceId << endl;
}

void AudioVideoInputListener::GetSupportedInputSourcesPropertyCallback(QStatus status, const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (ER_OK == status) {
        for(AudioVideoInputInterface::InputSources::const_iterator citer = supportedInputSources.begin();
            citer != supportedInputSources.end(); citer++) {
            cout << citer->first << " "
                 << citer->second.sourceType << " "
                 << (int)citer->second.signalPresence << " "
                 << citer->second.portNumber << " "
                 << citer->second.friendlyName.c_str() << " " << endl;
        }
    }
}

void AudioVideoInputListener::SetInputSourceIdPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

AudioVideoInputCommands::AudioVideoInputCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

AudioVideoInputCommands::~AudioVideoInputCommands()
{
}

void AudioVideoInputCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(AUDIO_VIDEO_INPUT_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<AudioVideoInputIntfController*>(haeInterface);
    }

    RegisterCommand(&AudioVideoInputCommands::OnCmdGetInputSourceId, "gis", "get input source id");
    RegisterCommand(&AudioVideoInputCommands::OnCmdSetInputSourceId, "sis", "set input source id (use 'si <id>')");
    RegisterCommand(&AudioVideoInputCommands::OnCmdGetSupportedInputSources, "gsis", "get supported input sources");
    PrintCommands();
}

void AudioVideoInputCommands::OnCmdGetInputSourceId(Commands* commands, std::string& cmd)
{
    AudioVideoInputIntfController* intfController = static_cast<AudioVideoInputCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetInputSourceId();
}

void AudioVideoInputCommands::OnCmdSetInputSourceId(Commands* commands, std::string& cmd)
{
    AudioVideoInputIntfController* intfController = static_cast<AudioVideoInputCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int inputSourceId = strtol(cmd.c_str(), NULL, 10);
    if (inputSourceId < 0 || inputSourceId >= 65536) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetInputSourceId((uint16_t)inputSourceId);
}

void AudioVideoInputCommands::OnCmdGetSupportedInputSources(Commands* commands, std::string& cmd)
{
    AudioVideoInputIntfController* intfController = static_cast<AudioVideoInputCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedInputSources();
}
