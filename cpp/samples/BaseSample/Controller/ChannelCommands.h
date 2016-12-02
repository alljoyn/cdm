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

#ifndef CHANNELCOMMANDS_H_
#define CHANNELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ChannelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class ChannelListener : public ChannelIntfControllerListener {
  public:
    ChannelListener();
    virtual ~ChannelListener();
    virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& channelId, void* context);
    virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t totalNumberOfChannels, void* context);
    virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords,
                                          void* context, const char* errorName, const char* errorMessage);
    virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& channelId);
    virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t totalNumberOfChannels);
    virtual void OnChannelListChanged(const qcc::String& objectPath);
};

class ChannelCommands : public InterfaceCommands
{
  public:
    ChannelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~ChannelCommands();

    virtual void Init();

    ChannelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetChannelId(Commands* commands, std::string& cmd);
    static void OnCmdGetTotalNumberOfChannels(Commands* commands, std::string& cmd);
    static void OnCmdSetChannelId(Commands* commands, std::string& cmd);
    static void OnCmdGetChannelList(Commands* commands, std::string& cmd);

  private:
    ChannelIntfController* m_intfController;
    ChannelListener m_listener;
};


#endif /* CHANNELCOMMANDS_H_ */