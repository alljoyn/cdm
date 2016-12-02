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
    virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t volume, void* context);
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

    AudioVolumeIntfController* GetInterface() { return m_intfController.get(); }
    static void OnCmdGetVolume(Commands* commands, std::string& cmd);
    static void OnCmdSetVolume(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxVolume(Commands* commands, std::string& cmd);
    static void OnCmdGetMute(Commands* commands, std::string& cmd);
    static void OnCmdSetMute(Commands* commands, std::string& cmd);

  private:
    AudioVolumeIntfControllerPtr m_intfController;
    AudioVolumeListener m_listener;
};


#endif /* AUDIOVOLUMECOMMANDS_H_ */
