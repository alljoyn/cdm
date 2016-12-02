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

#ifndef AUDIOVOLUMELISTENER_H_
#define AUDIOVOLUMELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class AudioVolumeListener : public AudioVolumeIntfControlleeListener
{
  public:
    virtual QStatus OnSetVolume(const uint8_t& volume);
    virtual QStatus OnGetVolume(uint8_t& volume);
    virtual QStatus OnSetMute(const bool& mute);
    virtual QStatus OnGetMute(bool& mute);
    virtual QStatus OnGetMaxVolume(uint8_t& maxVolume);
};

class AudioVolumeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    AudioVolumeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~AudioVolumeCommands();

    virtual void Init();

    AudioVolumeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetVolume(Commands* commands, std::string& cmd);
    static void OnCmdSetVolume(Commands* commands, std::string& cmd);
    static void OnCmdGetMute(Commands* commands, std::string& cmd);
    static void OnCmdSetMute(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxVolume(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxVolume(Commands* commands, std::string& cmd);

  private:
    AudioVolumeIntfControllee* m_intfControllee;
    AudioVolumeListener m_listener;
};

#endif /* AUDIOVOLUMELISTENER_H_ */