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

#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfController.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllerListener.h>

class CurrentPowerListener : public CurrentPowerIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    double m_currentPower;
    double m_precision;
    uint16_t m_updateMinTime;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double currentPower, void* context)
    {
        this->m_status = status;
        this->m_currentPower = currentPower;
        m_event.SetEvent();
    }

    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context)
    {
        this->m_status = status;
        this->m_precision = precision;
        m_event.SetEvent();
    }

    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context)
    {
        this->m_status = status;
        this->m_updateMinTime = updateMinTime;
        m_event.SetEvent();
    }

    virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double currentPower)
    {
        this->m_currentPower = currentPower;
        m_eventSignal.SetEvent();
    }

    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision)
    {
        this->m_precision = precision;
        m_eventSignal.SetEvent();
    }

    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime)
    {
        this->m_updateMinTime = updateMinTime;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_CurrentPower)
{
    WaitForControllee(CURRENT_POWER_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        CurrentPowerListener listener;
        CdmInterface* interface = m_controller->CreateInterface(CURRENT_POWER_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        CurrentPowerIntfController* controller = static_cast<CurrentPowerIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retrieve the CurrentPower property.");
            status = controller->GetCurrentPower();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the Precision property.");
            status = controller->GetPrecision();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the UpdateMinTime property.");
            status = controller->GetUpdateMinTime();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}