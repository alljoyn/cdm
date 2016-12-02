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

    AudioVideoInputIntfController* GetInterface() { return m_intfController.get(); }

    static void OnCmdGetInputSourceId(Commands* commands, std::string& cmd);
    static void OnCmdSetInputSourceId(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedInputSources(Commands* commands, std::string& cmd);

  private:
    AudioVideoInputIntfControllerPtr m_intfController;
    AudioVideoInputListener m_listener;
};

#endif /* AUDIOVIDEOINPUTCOMMANDS_H_ */
