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

#include "CdmTest.h"
#include <algorithm>

#include <interfaces/controller/environment/TargetTemperatureLevelIntfController.h>
#include <interfaces/controller/environment/TargetTemperatureLevelIntfControllerListener.h>

class TargetTemperatureLevelListener : public TargetTemperatureLevelIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint8_t m_targetLevel;
    uint8_t m_maxLevel;
    std::vector<uint8_t> m_selectableTemperatureLevels;
    uint8_t m_targetLevelSignal;
    uint8_t m_maxLevelSignal;
    std::vector<uint8_t> m_selectableTemperatureLevelsSignal;

    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_targetLevel = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_maxLevel = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
    {
        m_status = status;
        m_selectableTemperatureLevels = value;
        m_event.SetEvent();
    }

    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_targetLevelSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_maxLevelSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
    {
        m_selectableTemperatureLevelsSignal = value;
        m_eventSignal.SetEvent();
    }

    QStatus GetUnselectableLevel(uint8_t& unselectableLevel)
    {
        for(uint8_t i = 0; i <= m_maxLevel; i++)
        {
            std::vector<uint8_t>::iterator it;
            it = std::find(m_selectableTemperatureLevels.begin(),m_selectableTemperatureLevels.end(), i);
            if(it == m_selectableTemperatureLevels.end())
            {
                unselectableLevel = i;
                return ER_OK;
            }
        }
        return ER_FAIL;
    }
};

TEST_F(CDMTest, CDM_v1_TargetTemperatureLevel)
{
    WaitForControllee(TARGET_TEMPERATURE_LEVEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<TargetTemperatureLevelListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel", m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<TargetTemperatureLevelIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the TargetLevel property.");
            status = controller->GetTargetLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the MaxLevel property.");
            status = controller->GetMaxLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the SelectableTemperatureLevels property.");
            status = controller->GetSelectableTemperatureLevels();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();
        }

        uint8_t target = listener->m_targetLevel;
        if (listener->m_selectableTemperatureLevelsSignal.size() > 0) {
            TEST_LOG_1("Initialize all read-write properties.");
            {
                TEST_LOG_2("Initialize the TargetLevel property to the 1st item of SelectableTemperatureLevels.");
                if (listener->m_targetLevel != listener->m_selectableTemperatureLevels[0]) {
                    target = listener->m_selectableTemperatureLevels[0];
                    status =  controller->SetTargetLevel(target);
                    EXPECT_EQ(status, ER_OK);
                    EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                    EXPECT_EQ(listener->m_status, ER_OK);
                    listener->m_event.ResetEvent();

                    EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                    listener->m_eventSignal.ResetEvent();
                    EXPECT_EQ(listener->m_targetLevelSignal, listener->m_selectableTemperatureLevels[0]);
                }
            }

            if (listener->m_selectableTemperatureLevelsSignal.size() > 1) {
                TEST_LOG_1("Set properties to valid value.");
                {
                    TEST_LOG_2("Set the TargetLevel property to the 2nd item of SelectableTemperatureLevels.");
                    target = listener->m_selectableTemperatureLevels[1];
                    status =  controller->SetTargetLevel(target);
                    EXPECT_EQ(status, ER_OK);
                    EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                    EXPECT_EQ(listener->m_status, ER_OK);
                    listener->m_event.ResetEvent();

                    TEST_LOG_3("Wait the PropertiesChanged signal for the TargetLevel property.");
                    EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                    listener->m_eventSignal.ResetEvent();
                    EXPECT_EQ(listener->m_targetLevelSignal, target);

                    TEST_LOG_3("Get the TargetLevel property.");
                    status =  controller->GetTargetLevel();
                    EXPECT_EQ(status, ER_OK);
                    EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                    listener->m_event.ResetEvent();
                    EXPECT_EQ(listener->m_status, ER_OK);
                    EXPECT_EQ(listener->m_targetLevel, target);
                }
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the TargetLevel property to value outside SelectableLevels.");
            uint8_t unselectableLevel = 0;
            status = listener->GetUnselectableLevel(unselectableLevel);
            if(status == ER_OK)
            {
                status = controller->SetTargetLevel(unselectableLevel);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_NE(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                TEST_LOG_2("Get the TargetLevel property.");
                status = controller->GetTargetLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_targetLevel, target);
            }
        }
    }
}