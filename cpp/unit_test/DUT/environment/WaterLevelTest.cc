/******************************************************************************
 * 
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 * 
 *    SPDX-License-Identifier: Apache-2.0
 * 
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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
#include <iostream>
using namespace std;

#include <interfaces/controller/environment/WaterLevelIntfController.h>
#include <interfaces/controller/environment/WaterLevelIntfControllerListener.h>

class WaterLevelListener : public WaterLevelIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;

    uint8_t m_maxLevel;
    uint8_t m_maxLevelSignal;

    uint8_t m_currentLevel;
    uint8_t m_currentLevelSignal;

    WaterLevelInterface::SupplySource m_supplySource;
    WaterLevelInterface::SupplySource m_supplySourceSignal;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
    {
        m_maxLevel = value;
        m_status = status;
        m_event.SetEvent();
    }
    virtual void OnResponseGetSupplySource(QStatus status, const qcc::String& objectPath, const WaterLevelInterface::SupplySource value, void* context) override
    {
        m_status = status;
        m_supplySource = value;
        m_event.SetEvent();
    }
    virtual void OnResponseGetCurrentLevel (QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
    {
        m_status = status;
        m_currentLevel = value;
        m_event.SetEvent();
    }
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) override
    {
        m_maxLevelSignal = value;
        m_eventSignal.SetEvent();
    }
    virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value) override
    {
        m_currentLevelSignal = value;
        m_eventSignal.SetEvent();
    }
    virtual void OnSupplySourceChanged(const qcc::String& objectPath, const WaterLevelInterface::SupplySource value) override
    {
        m_supplySourceSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_WaterLevel)
{
    WaitForControllee(WATER_LEVEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<WaterLevelListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Environment.WaterLevel", m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<WaterLevelIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the MaxLevel property.");
            status = controller->GetMaxLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the CurrentLevel property.");
            status = controller->GetCurrentLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve SupplySource property.");
            status = controller->GetSupplySource();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }
    }
}
