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

#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllerListener.h>

class TargetTemperatureListener : public TargetTemperatureIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    double m_targetValue;
    double m_minValue;
    double m_maxValue;
    double m_stepValue;
    double m_targetValueSignal;
    double m_minValueSignal;
    double m_maxValueSignal;
    double m_stepValueSignal;

    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_targetValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_minValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_maxValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_stepValue = value;
        m_event.SetEvent();
    }

    virtual void OnTargetValueChanged(const qcc::String& objectPath, const double value)
    {
        m_targetValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value)
    {
        m_minValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value)
    {
        m_maxValueSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnStepValueChanged(const qcc::String& objectPath, const double value)
    {
        m_stepValueSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_TargetTemperature)
{
    WaitForControllee(TARGET_TEMPERATURE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        TargetTemperatureListener listener;
        CdmInterface* interface = m_controller->CreateInterface(TARGET_TEMPERATURE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        TargetTemperatureIntfController* controller = static_cast<TargetTemperatureIntfController*>(interface);
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
        }

        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the TargetValue property to MinValue.");
            if (listener.m_targetValue != listener.m_minValue) {
                status =  controller->SetTargetValue(listener.m_minValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_targetValueSignal, listener.m_minValue);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("Set the TargetValue property to MaxValue.");
            double target = listener.m_maxValue;
            status =  controller->SetTargetValue(target);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
            listener.m_eventSignal.ResetEvent();
            EXPECT_DOUBLE_EQ(listener.m_targetValueSignal, target);

            TEST_LOG_3("Get the TargetValue property.");
            status =  controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_DOUBLE_EQ(listener.m_targetValue, target);

            TEST_LOG_2("If StepValue != 0, Set the TargetValue property to MinValue + StepValue.");
            if (listener.m_stepValue != 0) {
                target = listener.m_minValue + listener.m_stepValue;
            } else {
                TEST_LOG_2("Else, Set the TargetValue property to MinValue + (MaxValue - MinValue)/2.");
                target = listener.m_minValue + (listener.m_maxValue - listener.m_minValue)/2.0;
            }
            status =  controller->SetTargetValue(target);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
            listener.m_eventSignal.ResetEvent();
            EXPECT_DOUBLE_EQ(listener.m_targetValueSignal, target);

            TEST_LOG_3("Get the TargetValue property.");
            status =  controller->GetTargetValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_DOUBLE_EQ(listener.m_targetValue, target);
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("If MinValue > DBL_MIN, Set the TargetValue property to the DBL_MIN.");
            if (listener.m_minValue > DBL_MIN) {
                status =  controller->SetTargetValue(DBL_MIN);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_DOUBLE_EQ(listener.m_targetValueSignal, listener.m_minValue);

                TEST_LOG_3("Get the TargetValue property.");
                status =  controller->GetTargetValue();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_DOUBLE_EQ(listener.m_targetValue, listener.m_minValue);
            }

            TEST_LOG_2("If MaxValue < DBL_MAX, Set the TargetValue property to the DBL_MAX.");
            if (listener.m_maxValue < DBL_MAX) {
                status =  controller->SetTargetValue(DBL_MAX);
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
                EXPECT_DOUBLE_EQ(listener.m_targetValue, listener.m_maxValue);
            }

            TEST_LOG_2("If StepValue != 0, Set the TargetValue property to MinValue + (StepValue/3).");
            if (listener.m_stepValue != 0) {
                double target = listener.m_minValue + (listener.m_stepValue/3.0);
                status =  controller->SetTargetValue(target);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the TargetValue property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_TRUE((listener.m_targetValueSignal == listener.m_minValue) ||
                            (listener.m_targetValueSignal == listener.m_minValue + listener.m_stepValue));

                TEST_LOG_3("Get the TargetValue property.");
                status =  controller->GetTargetValue();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_TRUE((listener.m_targetValue == listener.m_minValue) ||
                            (listener.m_targetValue == listener.m_minValue + listener.m_stepValue));
            }
        }
   }
}