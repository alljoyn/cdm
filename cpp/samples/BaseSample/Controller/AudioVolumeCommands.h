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

#ifndef AUDIOVOLUMECOMMANDS_H_
#define AUDIOVOLUMECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class AudioVolumeListener : public AudioVolumeIntfControllerListener {
  public:
    AudioVolumeListener();
    virtual ~AudioVolumeListener();
    virtual void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, uint8_t volume, void* context);
    virtual void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t maxVolume, void* context);
    virtual void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool mute, void* context);
    virtual void OnVolumeChanged(const qcc::String& objectPath, const uint8_t volume);
    virtual void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t maxVolume);
    virtual void OnMuteChanged(const qcc::String& objectPath, const bool mute);
};

class AudioVolumeCommands : public InterfaceCommands
{
  public:
    AudioVolumeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~AudioVolumeCommands();

    virtual void Init();

    AudioVolumeIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetVolume(Commands* commands, std::string& cmd);
    static void OnCmdSetVolume(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxVolume(Commands* commands, std::string& cmd);
    static void OnCmdGetMute(Commands* commands, std::string& cmd);
    static void OnCmdSetMute(Commands* commands, std::string& cmd);

  private:
    AudioVolumeIntfController* m_intfController;
    AudioVolumeListener m_listener;
};


#endif /* AUDIOVOLUMECOMMANDS_H_ */