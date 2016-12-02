/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "AudioVideoInputCommands.h"
#include "ControllerSample.h"

AudioVideoInputListener::AudioVideoInputListener()
{
}

AudioVideoInputListener::~AudioVideoInputListener()
{
}

void AudioVideoInputListener::OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void AudioVideoInputListener::OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const uint16_t inputSourceId, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "inputSourceId: " << inputSourceId << endl;
}

void AudioVideoInputListener::OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources, void* context)
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

void AudioVideoInputListener::OnInputSourceIdChanged(const qcc::String& objectPath, const uint16_t inputSourceId)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "inputSourceId: " << inputSourceId << endl;
}

void AudioVideoInputListener::OnSupportedInputSourcesChanged(const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources)
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
        CdmInterface* cdmInterface = m_sample->CreateInterface(AUDIO_VIDEO_INPUT_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<AudioVideoInputIntfController*>(cdmInterface);
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