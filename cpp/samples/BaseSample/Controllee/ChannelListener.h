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