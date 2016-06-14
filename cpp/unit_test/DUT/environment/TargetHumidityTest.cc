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

#include <alljoyn/hae/interfaces/environment/TargetHumidityIntfController.h>
#include <alljoyn/hae/interfaces/environment/TargetHumidityIntfControllerListener.h>
#include <algorithm>

class TargetHumidityListener : public TargetHumidityIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint8_t m_targetValue;
    uint8_t m_minValue;
    uint8_t m_maxValue;
    uint8_t m_stepValue;
    TargetHumidityInterface::HumidityLevels m_selectableHumidityLevels;
    uint8_t m_targetValueSignal;
    uint8_t m_minValueSignal;
    uint8_t m_maxValueSignal;
    uint8_t m_stepValueSignal;
    TargetHumidityInterface::HumidityLevels m_selectableHumidityLevelsSignal;

    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_targetValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_minValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_maxValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_stepValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value, void* context)
    {
        m_status = status;
        m_selectableHumidityLevels = value;
        m_event.SetEvent();
    }

    virtual void OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_targetValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnMinValueChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_minValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_maxValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnStepValueChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_stepValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value)
    {
        m_selectableHumidityLevelsSignal = value;
        m_eventSignal.SetEvent();
    }
};

uint8_t getInvalidValue(TargetHumidityInterface::HumidityLevels& levels) {
    for (int i = TargetHumidityInterface::MIN_HUMIDITY; i < TargetHumidityInterface::MAX_HUMIDITY; ++i) {
        if (std::find(levels.begin(), levels.end(), i) == levels.end())
            return i;
    }
    return TargetHumidityInterface::MAX_HUMIDITY + 1;
}

TEST_F(HAETest, HAE_v1_TargetHumidity)
{
    WaitForControllee(TARGET_HUMIDITY_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        TargetHumidityListener listener;
        HaeInterface* interface = m_controller->CreateInterface(TARGET_HUMIDITY_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        TargetHumidityIntfController* controller = static_cast<TargetHumidityIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the TargetValue property.");
            status = controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the MinValue property.");
            status = controller->GetMinValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the MaxValue property.");
            status = controller->GetMaxValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the StepValue property.");
            status = controller->GetStepValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the SelectableHumidityLevels property.");
            status = controller->GetSelectableHumidityLevels();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();
        }

        TEST_LOG_1("Initialize all read-write properties.");
        if (listener.m_maxValue > listener.m_minValue) {
            TEST_LOG_2("Initialize the TargetValue property to the MinValue");
            if (listener.m_targetValue != listener.m_minValue) {
                uint8_t target = listener.m_minValue;
                status =  controller->SetTargetValue(target);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_targetValueSignal, target);
            }
        } else {
            TEST_LOG_2("If SelectableHumidityLevels > 1, initialize the TargetValue property to the 1st item of the SelectableHumidityLevels.");
            if (listener.m_selectableHumidityLevels.size() > 1 && listener.m_targetValue != listener.m_selectableHumidityLevels[0]) {
                uint8_t target = listener.m_selectableHumidityLevels[0];
                status =  controller->SetTargetValue(target);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_targetValueSignal, target);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        if (listener.m_maxValue > listener.m_minValue) {
            TEST_LOG_2("Set the TargetValue property to the MaxValue.");
            uint8_t target = listener.m_maxValue;
            status =  controller->SetTargetValue(target);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
            listener.m_eventSignal.ResetEvent();
            EXPECT_EQ(listener.m_targetValueSignal, target);

            TEST_LOG_3("Get the TargetValue property.");
            status =  controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_EQ(listener.m_targetValue, target);
        } else if (listener.m_selectableHumidityLevels.size() > 1) {
            TEST_LOG_2("If SelectableHumidityLevels > 1, Set the TargetValue property to the 2nd item of the SelectableHumidityLevels.");
            uint8_t target = listener.m_selectableHumidityLevels[1];
            status =  controller->SetTargetValue(target);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
            listener.m_eventSignal.ResetEvent();
            EXPECT_EQ(listener.m_targetValueSignal, target);

            TEST_LOG_3("Get the TargetValue property.");
            status =  controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_EQ(listener.m_targetValue, target);
        }

        TEST_LOG_1("Set properties to invalid value.");
        if (listener.m_maxValue > listener.m_minValue) {
            TEST_LOG_2("If MinValue > " << (int)TargetHumidityInterface::MIN_HUMIDITY << ", Set the TargetValue property to the 0.");
            if (listener.m_minValue > TargetHumidityInterface::MIN_HUMIDITY) {
                status =  controller->SetTargetValue(TargetHumidityInterface::MIN_HUMIDITY);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_targetValueSignal, listener.m_minValue);

                TEST_LOG_3("Get the TargetValue property.");
                status =  controller->GetTargetValue();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_targetValue, listener.m_minValue);
            }

            TEST_LOG_2("Set the TargetValue property to invalid Value(" << (int)TargetHumidityInterface::MAX_HUMIDITY + 1 << ").");
            status =  controller->SetTargetValue(TargetHumidityInterface::MAX_HUMIDITY + 1);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
            listener.m_eventSignal.ResetEvent();
            EXPECT_DOUBLE_EQ(listener.m_targetValueSignal, listener.m_maxValue);

            TEST_LOG_3("Get the TargetValue property.");
            status =  controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_EQ(listener.m_targetValue, listener.m_maxValue);
        } else if (listener.m_selectableHumidityLevels.size() > 0) {
            uint8_t prevValue = listener.m_targetValue;
            uint8_t targetValue = getInvalidValue(listener.m_selectableHumidityLevels);
            TEST_LOG_2("Set the TargetValue property to invalid Value(" << (int)targetValue << ").");
            status =  controller->SetTargetValue(targetValue);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_NE(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_3("Get the TargetValue property.");
            status =  controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_EQ(listener.m_targetValue, prevValue);
        }
    }
}
