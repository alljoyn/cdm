/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "CdmTest.h"

#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllerListener.h>

class FilterStatusListener : public FilterStatusIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint16_t m_expectedLifeInDays;
    bool m_isCleanable;
    uint8_t m_orderPercentage;
    qcc::String m_manufacturer;
    qcc::String m_partNumber;
    qcc::String m_url;
    uint8_t m_lifeRemaining;

    virtual void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        m_status = status;
        m_expectedLifeInDays = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool isCleanable, void* context)
    {
        m_status = status;
        m_isCleanable = isCleanable;
        m_event.SetEvent();
    }

    virtual void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_orderPercentage = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& manufacturer, void* context)
    {
        m_status = status;
        m_manufacturer = manufacturer;
        m_event.SetEvent();
    }

    virtual void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& partNumber, void* context)
    {
        m_status = status;
        m_partNumber = partNumber;
        m_event.SetEvent();
    }

    virtual void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& url, void* context)
    {
        m_status = status;
        m_url = url;
        m_event.SetEvent();
    }

    virtual void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_lifeRemaining = value;
        m_event.SetEvent();
    }

    virtual void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value)
    {
        m_expectedLifeInDays = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnIsCleanableChanged(const qcc::String& objectPath, const bool isCleanable)
    {
        m_isCleanable = isCleanable;
        m_eventSignal.SetEvent();
    }

    virtual void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_orderPercentage = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_lifeRemaining = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_FilterStatus)
{
    WaitForControllee(FILTER_STATUS_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        FilterStatusListener listener;
        CdmInterface* interface = m_controller->CreateInterface(FILTER_STATUS_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        FilterStatusIntfController* controller = static_cast<FilterStatusIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the ExpectedLifeInDays property.");
            status = controller->GetExpectedLifeInDays();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the IsCleanable property.");
            status = controller->GetIsCleanable();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the OrderPercentage property.");
            status = controller->GetOrderPercentage();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the Manufacturer property.");
            status = controller->GetManufacturer();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the PartNumber property.");
            status = controller->GetPartNumber();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the Url property.");
            status = controller->GetUrl();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the LifeRemaining property.");
            status = controller->GetLifeRemaining();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();
        }
   }
}