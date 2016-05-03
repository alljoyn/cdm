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

#ifndef AUDIOVIDEOINPUTLISTENER_H_
#define AUDIOVIDEOINPUTLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/AudioVideoInputIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AudioVideoInputIntfControlleeListener.h>

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
