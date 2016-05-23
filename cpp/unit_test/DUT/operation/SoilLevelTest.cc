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

#include <alljoyn/hae/interfaces/operation/SoilLevelIntfController.h>
#include <alljoyn/hae/interfaces/operation/SoilLevelIntfControllerListener.h>

class SoilLevelListener : public SoilLevelIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;

    uint8_t m_maxLevel;
    uint8_t m_maxLevelSignal;

    uint8_t m_targetLevel;
    uint8_t m_targetLevelSignal;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    std::vector<uint8_t> m_selectableLevels;
    std::vector<uint8_t> m_selectableLevelsSignal;

    virtual void GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context)
    {
        m_status = status;
        m_maxLevel = maxLevel;
        m_event.SetEvent();
    }

    virtual void GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context)
    {
        m_status = status;
        m_targetLevel = targetLevel;
        m_event.SetEvent();
    }

    virtual void SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context)
    {
        m_selectableLevels = selectableLevels;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel)
    {
        m_maxLevelSignal = maxLevel;
        m_eventSignal.SetEvent();
    }

    virtual void TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel)
    {
        m_targetLevelSignal = targetLevel;
        m_eventSignal.SetEvent();
    }

    virtual void SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels)
    {
        m_selectableLevelsSignal = selectableLevels;
        m_eventSignal.SetEvent();
    }
    QStatus GetUnselectableLevel(uint8_t& unselectableLevel)
    {
        for(uint8_t i = 0; i <= m_maxLevel; i++)
        {
            std::vector<uint8_t>::iterator it;
            it = std::find(m_selectableLevels.begin(),m_selectableLevels.end(), i);
            if(it == m_selectableLevels.end())
            {
                unselectableLevel = i;
                return ER_OK;
            }
        }
        return ER_FAIL;
    }
};

TEST_F(HAETest, HAE_v1_SoilLevelTest)
{
    WaitForControllee(SOIL_LEVEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        SoilLevelListener listener;
        HaeInterface* interface = m_controller->CreateInterface(SOIL_LEVEL_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        SoilLevelIntfController* controller = static_cast<SoilLevelIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the MaxLevel property.");
            status = controller->GetMaxLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the TargetLevel property.");
            status = controller->GetTargetLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve SelectableLevels property.");
            status = controller->GetSelectableLevels();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        const uint8_t initTargetLevel = listener.m_selectableLevels[0];
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the TargetLevel property to the 1st item of the selectableLevels.");
            if (listener.m_targetLevel != initTargetLevel) {
                status = controller->SetTargetLevel(initTargetLevel);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_targetLevelSignal, initTargetLevel);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the TargetLevel property to MaxLevel + 1.");
            status = controller->SetTargetLevel(listener.m_maxLevel + 1);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);

            TEST_LOG_2("Get the TargetLevel property.");
            status = controller->GetTargetLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_EQ(listener.m_targetLevel, initTargetLevel);

            TEST_LOG_2("Set the TargetLevel property to value outside SelectableLevels.");
            uint8_t unselectableLevel = 0;
            status = listener.GetUnselectableLevel(unselectableLevel);
            if(status == ER_OK)
            {
                status = controller->SetTargetLevel(unselectableLevel);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_2("Get the TargetLevel property.");
                status = controller->GetTargetLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_targetLevel, initTargetLevel);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If SelectableLevels > 1, set the TargetLevel property to the 2nd item of the SelectableLevels.");
            if (listener.m_selectableLevels.size() > 1) {
                const uint8_t validTargetLevel = listener.m_selectableLevels[1];
                status = controller->SetTargetLevel(validTargetLevel);

                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the TargetLevel property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_targetLevelSignal, validTargetLevel);

                TEST_LOG_3("Get the TargetLevel property.");
                status = controller->GetTargetLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_targetLevel, validTargetLevel);
            }
        }
    }
}
