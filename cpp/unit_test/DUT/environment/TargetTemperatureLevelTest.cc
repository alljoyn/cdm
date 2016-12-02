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

#include "CdmTest.h"
#include <algorithm>

#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllerListener.h>

class TargetTemperatureLevelListener : public TargetTemperatureLevelIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint8_t m_targetLevel;
    uint8_t m_maxLevel;
    TargetTemperatureLevelInterface::TemperatureLevels m_selectableTemperatureLevels;
    uint8_t m_targetLevelSignal;
    uint8_t m_maxLevelSignal;
    TargetTemperatureLevelInterface::TemperatureLevels m_selectableTemperatureLevelsSignal;

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

    virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value, void* context)
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

    virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value)
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

        TargetTemperatureLevelListener listener;
        CdmInterface* interface = m_controller->CreateInterface(TARGET_TEMPERATURE_LEVEL_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        TargetTemperatureLevelIntfController* controller = static_cast<TargetTemperatureLevelIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the TargetLevel property.");
            status = controller->GetTargetLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the MaxLevel property.");
            status = controller->GetMaxLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the SelectableTemperatureLevels property.");
            status = controller->GetSelectableTemperatureLevels();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();
        }

        uint8_t target = listener.m_targetLevel;
        if (listener.m_selectableTemperatureLevelsSignal.size() > 0) {
            TEST_LOG_1("Initialize all read-write properties.");
            {
                TEST_LOG_2("Initialize the TargetLevel property to the 1st item of SelectableTemperatureLevels.");
                if (listener.m_targetLevel != listener.m_selectableTemperatureLevels[0]) {
                    target = listener.m_selectableTemperatureLevels[0];
                    status =  controller->SetTargetLevel(target);
                    EXPECT_EQ(status, ER_OK);
                    EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                    EXPECT_EQ(listener.m_status, ER_OK);
                    listener.m_event.ResetEvent();

                    EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                    listener.m_eventSignal.ResetEvent();
                    EXPECT_EQ(listener.m_targetLevelSignal, listener.m_selectableTemperatureLevels[0]);
                }
            }

            if (listener.m_selectableTemperatureLevelsSignal.size() > 1) {
                TEST_LOG_1("Set properties to valid value.");
                {
                    TEST_LOG_2("Set the TargetLevel property to the 2nd item of SelectableTemperatureLevels.");
                    target = listener.m_selectableTemperatureLevels[1];
                    status =  controller->SetTargetLevel(target);
                    EXPECT_EQ(status, ER_OK);
                    EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                    EXPECT_EQ(listener.m_status, ER_OK);
                    listener.m_event.ResetEvent();

                    TEST_LOG_3("Wait the PropertiesChanged signal for the TargetLevel property.");
                    EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                    listener.m_eventSignal.ResetEvent();
                    EXPECT_EQ(listener.m_targetLevelSignal, target);

                    TEST_LOG_3("Get the TargetLevel property.");
                    status =  controller->GetTargetLevel();
                    EXPECT_EQ(status, ER_OK);
                    EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                    listener.m_event.ResetEvent();
                    EXPECT_EQ(listener.m_status, ER_OK);
                    EXPECT_EQ(listener.m_targetLevel, target);
                }
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
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
                listener.m_event.ResetEvent();

                TEST_LOG_2("Get the TargetLevel property.");
                status = controller->GetTargetLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_targetLevel, target);
            }
        }
    }
}