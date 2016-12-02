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

#ifndef AUDIOVIDEOINPUTCOMMANDS_H_
#define AUDIOVIDEOINPUTCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class AudioVideoInputListener : public AudioVideoInputIntfControllerListener {
  public:
    AudioVideoInputListener();
    virtual ~AudioVideoInputListener();
    virtual void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const uint16_t inputSourceId, void* context);
    virtual void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources, void* context);
    virtual void OnInputSourceIdChanged(const qcc::String& objectPath, const uint16_t inputSourceId);
    virtual void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources);
};

class AudioVideoInputCommands : public InterfaceCommands
{
  public:
    AudioVideoInputCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~AudioVideoInputCommands();

    virtual void Init();

    AudioVideoInputIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetInputSourceId(Commands* commands, std::string& cmd);
    static void OnCmdSetInputSourceId(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedInputSources(Commands* commands, std::string& cmd);

  private:
    AudioVideoInputIntfController* m_intfController;
    AudioVideoInputListener m_listener;
};

#endif /* AUDIOVIDEOINPUTCOMMANDS_H_ */