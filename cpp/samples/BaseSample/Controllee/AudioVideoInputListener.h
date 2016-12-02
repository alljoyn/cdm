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

#ifndef AUDIOVIDEOINPUTLISTENER_H_
#define AUDIOVIDEOINPUTLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class AudioVideoInputListener : public AudioVideoInputIntfControlleeListener
{
  public:
    virtual QStatus OnSetInputSourceId(const uint16_t& inputSourceId);
    virtual QStatus OnGetInputSourceId(uint16_t& inputSourceId);
    virtual QStatus OnGetSupportedInputSources(AudioVideoInputInterface::InputSources& supportedInputSources);
};

class AudioVideoInputCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    AudioVideoInputCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~AudioVideoInputCommands();

    virtual void Init();
    virtual void InitializeProperties();

    AudioVideoInputIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetInputSourceId(Commands* commands, std::string& cmd);
    static void OnCmdSetInputSourceId(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedInputSources(Commands* commands, std::string& cmd);

  private:
    AudioVideoInputIntfControllee* m_intfControllee;
    AudioVideoInputListener m_listener;
};

#endif /* AUDIOVIDEOINPUTLISTENER_H_ */