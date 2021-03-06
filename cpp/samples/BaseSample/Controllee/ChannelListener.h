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

#ifndef CHANNELLISTENER_H_
#define CHANNELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

#define TOTAL_NUM_OF_CHANNEL 50
#define CHANNELID_PREFIX "CHANNEL_ID_"

class ChannelListener : public ChannelIntfControlleeListener
{
  public:
    virtual QStatus OnSetChannelId(const qcc::String& channelId);
    virtual QStatus OnGetChannelId(qcc::String& channelId);
    virtual QStatus OnGetTotalNumberOfChannels(uint16_t& totalNumberOfChannels);
    virtual QStatus OnGetChannelList(const uint16_t& startingRecord, const uint16_t& numRecords,
                                     ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords,
                                     ErrorCode& errorCode);
};

class ChannelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    ChannelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~ChannelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    ChannelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetChannelId(Commands* commands, std::string& cmd);
    static void OnCmdSetChannelId(Commands* commands, std::string& cmd);
    static void OnCmdGetTotalNumberOfChannels(Commands* commands, std::string& cmd);
    static void OnCmdSetTotalNumberOfChannels(Commands* commands, std::string& cmd);
    static void OnCmdEmitChannelListChanged(Commands* commands, std::string& cmd);

  private:
    ChannelIntfControllee* m_intfControllee;
    ChannelListener m_listener;
};

#endif /* CHANNELLISTENER_H_ */
