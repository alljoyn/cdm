/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "CdmTest.h"
#include <algorithm>

#include <interfaces/controller/operation/ChannelIntfController.h>
#include <interfaces/controller/operation/ChannelIntfControllerListener.h>

class ChannelListener : public ChannelIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;
    qcc::String m_channelId;
    uint16_t m_totalNumberOfChannels;
    qcc::String m_channelIdSignal;
    uint16_t m_totalNumberOfChannelsSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    std::vector<ChannelInterface::ChannelInfoRecord> m_channelInfoRecords;

    virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& channelId, void* context) override
    {
        m_channelId = channelId;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t totalNumberOfChannels, void* context) override
    {
        m_totalNumberOfChannels = totalNumberOfChannels;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const std::vector<ChannelInterface::ChannelInfoRecord>& listOfChannelInfoRecords,
                                          void* context, const char* errorName, const char* errorMessage) override
    {
        m_channelInfoRecords = listOfChannelInfoRecords;
        m_status = status;
        if (status != ER_OK) {
            if (errorName) {
                m_errorName = errorName;
            }
            if (errorMessage) {
                m_errorMessage = errorMessage;
            }
        }
        m_event.SetEvent();
    }

    virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& channelId) override
    {
        m_channelIdSignal = channelId;
        m_eventSignal.SetEvent();
    }

    virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t totalNumberOfChannels) override
    {
        m_totalNumberOfChannelsSignal = totalNumberOfChannels;
        m_eventSignal.SetEvent();
    }

    virtual void OnChannelListChanged(const qcc::String& objectPath) override
    {
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_Channel)
{
    WaitForControllee(CHANNEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<ChannelListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.Channel", m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<ChannelIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the ChannelId property.");
            status = controller->GetChannelId();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the TotalNumberOfChannels property.");
            status = controller->GetTotalNumberOfChannels();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Calls GetChannelList method with following.");
            {
                TEST_LOG_3("startingRecord = 0");
                TEST_LOG_3("numRecords = min(100, TotalNumberOfChannels)");
                uint16_t startingRecord = 0;
                uint16_t numRecords = std::min(listener->m_totalNumberOfChannels, (uint16_t) 100);
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                ASSERT_EQ(listener->m_channelInfoRecords.size(), numRecords);
            }
        }

        const qcc::String initChannelId = listener->m_channelInfoRecords[0].channelID;
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the ChannelId property to the 1st item of the ChannelList.");
            if (listener->m_channelId != initChannelId) {
                status = controller->SetChannelId(initChannelId);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_channelIdSignal, initChannelId);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the ChannelId property to “Invalid_ChannelId.");
            status = controller->SetChannelId("Invalid_ChannelId");
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_NE(listener->m_status, ER_OK);

            TEST_LOG_2("Get the ChannelId property.");
            status = controller->GetChannelId();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_STREQ(listener->m_channelId.c_str(), initChannelId.c_str());
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If TotalNumberOfChannels > 1, set the ChannelId property to the 2nd item of the ChannelList.");
            if (listener->m_channelInfoRecords.size() > 1) {
                const qcc::String validChannelId = listener->m_channelInfoRecords[1].channelID;
                status = controller->SetChannelId(validChannelId);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Channel property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_channelIdSignal, validChannelId);

                TEST_LOG_3("Get the Channel property.");
                status = controller->GetChannelId();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_channelId, validChannelId);
            }
        }

        TEST_LOG_1("Call method with invalid params");
        {
            TEST_LOG_2("Call the GetChannelList method with invalid startingRecord param as following.");
            {
                TEST_LOG_3("startingRecord = TotalNumberOfChannels + 1");
                TEST_LOG_3("numRecords = 50");
                const uint16_t startingRecord = listener->m_totalNumberOfChannels + 1;
                const uint16_t numRecords = 50;
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_NE(listener->m_status, ER_OK);
                EXPECT_STREQ(listener->m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());
            }

            TEST_LOG_2("Call the GetChannelList method with invalid numRecords param as following.");
            {
                TEST_LOG_3("startingRecord = max(0, TotalNumberOfChannels – 50)");
                TEST_LOG_3("numRecords = 100");
                const uint16_t startingRecord = std::max(0, listener->m_totalNumberOfChannels - 50);
                const uint16_t numRecords = 100;
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ((int)listener->m_channelInfoRecords.size(), listener->m_totalNumberOfChannels - startingRecord);
            }
        }

        TEST_LOG_1("Call method with valid params");
        {
            TEST_LOG_2("Call the GetChannelList method with valid startingRecord param as following.");
            {
                TEST_LOG_3("startingRecord = 0");
                TEST_LOG_3("numRecords = min(100, TotalNumberOfChannels)");
                const uint16_t startingRecord = 0;
                const uint16_t numRecords = std::min((uint16_t) 100, listener->m_totalNumberOfChannels);
                status = controller->GetChannelList(startingRecord, numRecords);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
            }
        }
    }
}