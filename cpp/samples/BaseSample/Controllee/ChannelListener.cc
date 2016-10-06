/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "ChannelListener.h"
#include "ControlleeSample.h"

using namespace std;

#define CHANNELNAME_PREFIX "CHANNEL_NAME_"
#define CHANNELNO_PREFIX "CHANNEL_NO_"

QStatus ChannelListener::OnSetChannelId(const qcc::String& channelId)
{
    cout << "ChannelListener::OnSetChannelId() - channelId : " << channelId << endl;
    for (int i = 0; i < TOTAL_NUM_OF_CHANNEL; i++) {
        ChannelInterface::ChannelInfoRecord chInfo;
        char buff[10];
        sprintf(buff, "%d", i);
        if (channelId.compare(CHANNELID_PREFIX + qcc::String(buff)) == 0) {
            return ER_OK;
        }
    }
    return ER_FAIL;
}

QStatus ChannelListener::OnGetChannelId(qcc::String& channelId)
{
    cout << "ChannelListener::OnGetChannelId()" << endl;
    return ER_OK;
}

QStatus ChannelListener::OnGetTotalNumberOfChannels(uint16_t& totalNumberOfChannels)
{
    cout << "ChannelListener::OnGetTotalNumberOfChannels()" << endl;
    totalNumberOfChannels = TOTAL_NUM_OF_CHANNEL;
    return ER_OK;
}

QStatus ChannelListener::OnGetChannelList(const uint16_t& startingRecord, const uint16_t& numRecords,
                                          ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords, ErrorCode& errorCode)
{
    cout << "ChannelListener::OnGetChannelList()" << endl;
    if (startingRecord > TOTAL_NUM_OF_CHANNEL - 1) {
        errorCode = INVALID_VALUE;
        return ER_FAIL;
    }

    for (int i = startingRecord; i < TOTAL_NUM_OF_CHANNEL && i < startingRecord+numRecords; i++) {
        ChannelInterface::ChannelInfoRecord chInfo;
        char buff[10];
        sprintf(buff, "%d", i);
        chInfo.channelId = CHANNELID_PREFIX + qcc::String(buff);
        chInfo.channelName = CHANNELNAME_PREFIX + qcc::String(buff);
        chInfo.channelNumber = CHANNELNO_PREFIX + qcc::String(buff);
        listOfChannelInfoRecords.push_back(chInfo);
    }
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* ChannelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new ChannelCommands(sample, objectPath);
}

ChannelCommands::ChannelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

ChannelCommands::~ChannelCommands()
{
}

void ChannelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CHANNEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<ChannelIntfControllee*>(cdmInterface);

        RegisterCommand(&ChannelCommands::OnCmdGetChannelId, "gci", "get channel id");
        RegisterCommand(&ChannelCommands::OnCmdSetChannelId, "sci", "set channel id (use 'sci <channel id>'");
        RegisterCommand(&ChannelCommands::OnCmdGetTotalNumberOfChannels, "gtnc", "get total number of channels");
        RegisterCommand(&ChannelCommands::OnCmdSetTotalNumberOfChannels, "stnc", "set total number of channels (use 'stnc <#>'");
        RegisterCommand(&ChannelCommands::OnCmdEmitChannelListChanged, "eclc", "emit channel list changed");
    } else {
        PrintCommands();
    }
}

void ChannelCommands::InitializeProperties()
{
    if (m_intfControllee) {
        qcc::String channelId = CHANNELID_PREFIX;
        channelId += "0";
        m_intfControllee->SetChannelId(channelId);
        m_intfControllee->SetTotalNumberOfChannels(TOTAL_NUM_OF_CHANNEL);
    }
}

void ChannelCommands::OnCmdGetChannelId(Commands* commands, std::string& cmd)
{
    ChannelIntfControllee* intfControllee = static_cast<ChannelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetChannelId() << endl;
}

void ChannelCommands::OnCmdSetChannelId(Commands* commands, std::string& cmd)
{
    ChannelIntfControllee* intfControllee = static_cast<ChannelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfControllee->SetChannelId(cmd.c_str());
}

void ChannelCommands::OnCmdGetTotalNumberOfChannels(Commands* commands, std::string& cmd)
{
    ChannelIntfControllee* intfControllee = static_cast<ChannelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetTotalNumberOfChannels() << endl;
}

void ChannelCommands::OnCmdSetTotalNumberOfChannels(Commands* commands, std::string& cmd)
{
    ChannelIntfControllee* intfControllee = static_cast<ChannelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int totalNumberOfChannels = strtol(cmd.c_str(), NULL, 10);
    if (totalNumberOfChannels < 0 || totalNumberOfChannels >= 65536) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetTotalNumberOfChannels((uint16_t)totalNumberOfChannels);
}

void ChannelCommands::OnCmdEmitChannelListChanged(Commands* commands, std::string& cmd)
{
    ChannelIntfControllee* intfControllee = static_cast<ChannelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfControllee->EmitChannelListChanged();
}