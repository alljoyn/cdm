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

#include "ChannelCommands.h"
#include "ControllerSample.h"

using namespace std;

ChannelListener::ChannelListener()
{
}

ChannelListener::~ChannelListener()
{
}

void ChannelListener::OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void ChannelListener::OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& channelId, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "channelId: " << channelId << endl;
}

void ChannelListener::OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t totalNumberOfChannels, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "totalNumberOfChannels: " << totalNumberOfChannels << endl;
}

void ChannelListener::OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords,
                                                   void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (ER_OK == status) {
        for(ChannelInterface::ChannelInfoRecords::const_iterator citer = listOfChannelInfoRecords.begin();
                citer != listOfChannelInfoRecords.end(); citer++)
        {
            cout << citer->channelID.c_str() << " "
                 << citer->channelNumber.c_str() << " "
                 << citer->channelName.c_str() << endl;
        }
    } else {
        cout << "error name : " << errorName << endl;
        cout << "error message : " << errorMessage << endl;
    }
}

void ChannelListener::OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& channelId)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "channelId: " << channelId << endl;
}

void ChannelListener::OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t totalNumberOfChannels)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "totalNumberOfChannels: " << totalNumberOfChannels << endl;
}

void ChannelListener::OnChannelListChanged(const qcc::String& objectPath)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
}

////////////////////////////////////////////////////////////////////////
ChannelCommands::ChannelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

ChannelCommands::~ChannelCommands()
{
}

void ChannelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CHANNEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<ChannelIntfController*>(cdmInterface);
    }

    RegisterCommand(&ChannelCommands::OnCmdGetChannelId, "gci", "get channel id");
    RegisterCommand(&ChannelCommands::OnCmdGetTotalNumberOfChannels, "gtnc", "get total number of channels");
    RegisterCommand(&ChannelCommands::OnCmdSetChannelId, "sci", "set channel id");
    RegisterCommand(&ChannelCommands::OnCmdGetChannelList, "gcl", "get channel list");
    PrintCommands();
}

void ChannelCommands::OnCmdGetChannelId(Commands* commands, std::string& cmd)
{
    ChannelIntfController* intfController = static_cast<ChannelCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetChannelId();
}

void ChannelCommands::OnCmdGetTotalNumberOfChannels(Commands* commands, std::string& cmd)
{
    ChannelIntfController* intfController = static_cast<ChannelCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetTotalNumberOfChannels();
}

void ChannelCommands::OnCmdSetChannelId(Commands* commands, std::string& cmd)
{
    ChannelIntfController* intfController = static_cast<ChannelCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->SetChannelId(cmd.c_str());
}

void ChannelCommands::OnCmdGetChannelList(Commands* commands, std::string& cmd)
{
    ChannelIntfController* intfController = static_cast<ChannelCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    uint16_t startingRecord = 0;
    uint16_t numRecords = 100;
    intfController->GetChannelList(startingRecord, numRecords);
}


