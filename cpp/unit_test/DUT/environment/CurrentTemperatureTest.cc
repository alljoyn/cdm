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

#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllerListener.h>


class CurrentTemperatureListener : public CurrentTemperatureIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    double m_currentValue;
    double m_precision;
    uint16_t m_updateMinTime;

    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_currentValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context)
    {
        m_status = status;
        m_precision = precision;
        m_event.SetEvent();
    }

    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context)
    {
        m_status = status;
        m_updateMinTime = updateMinTime;
        m_event.SetEvent();
    }

    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value)
    {
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_CurrentTemperature)
{
    WaitForControllee(CURRENT_TEMPERATURE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);
        CurrentTemperatureListener listener;
        CdmInterface* interface = m_controller->CreateInterface(CURRENT_TEMPERATURE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        CurrentTemperatureIntfController* controller = static_cast<CurrentTemperatureIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retrieve the CurrentValue property.");
            status = controller->GetCurrentValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the Precision property.");
            status = controller->GetPrecision();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the UpdateMinTime property.");
            status = controller->GetUpdateMinTime();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();
        }
    }
}