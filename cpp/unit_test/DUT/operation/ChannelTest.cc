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

#include "HaeTest.h"
#include <algorithm>

#include <alljoyn/hae/interfaces/operation/ChannelIntfController.h>
#include <alljoyn/hae/interfaces/operation/ChannelIntfControllerListener.h>

class ChannelListener : public ChannelIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    qcc::String m_channelId;
    uint16_t m_totalNumberOfChannels;
    qcc::String m_channelIdSignal;
    uint16_t m_totalNumberOfChannelsSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    ChannelInterface::ChannelInfoRecords m_channelInfoRecords;

    virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& channelId, void* context)
    {
        m_channelId = channelId;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t totalNumberOfChannels, void* context)
    {
        m_totalNumberOfChannels = totalNumberOfChannels;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords,
                                          void* context, const char* errorName, const char* errorMessage)
    {
        m_channelInfoRecords = listOfChannelInfoRecords;
        m_status = status;
        if (status != ER_OK) {
            if (errorName) m_errorName = errorName;
            if (errorMessage) m_errorMessage = errorMessage;
        }
        m_event.SetEvent();
    }

    virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& channelId)
    {
        m_channelIdSignal = channelId;
        m_eventSignal.SetEvent();
    }

    virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t totalNumberOfChannels)
    {
        m_totalNumberOfChannelsSignal = totalNumberOfChannels;
        m_eventSignal.SetEvent();
    }

    virtual void OnChannelListChanged(const qcc::String& objectPath)
    {
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_06)
{
    WaitForControllee(CHANNEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        ChannelListener listener;
        HaeInterface* interface = m_controller->CreateInterface(CHANNEL_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        ChannelIntfController* controller = static_cast<ChannelIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the ChannelId property.");
            status = controller->GetChannelId();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the TotalNumberOfChannels property.");
            status = controller->GetTotalNumberOfChannels();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Calls GetChannelList method with following.");
            {
                TEST_LOG_3("startingRecord = 0");
                TEST_LOG_3("numRecords = min(100, TotalNumberOfChannels)");
                uint16_t startingRecord = 0;
                uint16_t numRecords = std::min(listener.m_totalNumberOfChannels, (uint16_t) 100);
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                ASSERT_EQ(listener.m_channelInfoRecords.size(), numRecords);
            }
        }

        const qcc::String initChannelId = listener.m_channelInfoRecords[0].channelId;
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the ChannelId property to the 1st item of the ChannelList.");
            if (listener.m_channelId != initChannelId) {
                status = controller->SetChannelId(initChannelId);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_channelIdSignal, initChannelId);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the ChannelId property to “Invalid_ChannelId.");
            status = controller->SetChannelId("Invalid_ChannelId");
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);

            TEST_LOG_2("Get the ChannelId property.");
            status = controller->GetChannelId();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_STREQ(listener.m_channelId.c_str(), initChannelId.c_str());
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If TotalNumberOfChannels > 1, set the ChannelId property to the 2nd item of the ChannelList.");
            if (listener.m_channelInfoRecords.size() > 1) {
                const qcc::String validChannelId = listener.m_channelInfoRecords[1].channelId;
                status = controller->SetChannelId(validChannelId);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Channel property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_channelIdSignal, validChannelId);

                TEST_LOG_3("Get the Channel property.");
                status = controller->GetChannelId();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_channelId, validChannelId);
            }
        }

        TEST_LOG_1("Call method with invalid params");
        {
            TEST_LOG_2("Call the GetChannelList method with invalid startingRecord param as following.");
            {
                TEST_LOG_3("startingRecord = TotalNumberOfChannels + 1");
                TEST_LOG_3("numRecords = 50");
                const uint16_t startingRecord = listener.m_totalNumberOfChannels + 1;
                const uint16_t numRecords = 50;
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);
                EXPECT_STREQ(listener.m_errorName.c_str(), HaeInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());
            }

            TEST_LOG_2("Call the GetChannelList method with invalid numRecords param as following.");
            {
                TEST_LOG_3("startingRecord = max(0, TotalNumberOfChannels – 50)");
                TEST_LOG_3("numRecords = 100");
                const uint16_t startingRecord = std::max(0, listener.m_totalNumberOfChannels - 50);
                const uint16_t numRecords = 100;
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_channelInfoRecords.size(), listener.m_totalNumberOfChannels - startingRecord);
            }
        }

        TEST_LOG_1("Call method with valid params");
        {
            TEST_LOG_2("Call the GetChannelList method with valid startingRecord param as following.");
            {
                TEST_LOG_3("startingRecord = 0");
                TEST_LOG_3("numRecords = min(100, TotalNumberOfChannels)");
                const uint16_t startingRecord = 0;
                const uint16_t numRecords = std::min((uint16_t) 100, listener.m_totalNumberOfChannels);
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
            }
        }
    }
}
