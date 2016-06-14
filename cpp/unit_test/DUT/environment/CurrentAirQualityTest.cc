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

#include <alljoyn/hae/interfaces/environment/CurrentAirQualityIntfController.h>
#include <alljoyn/hae/interfaces/environment/CurrentAirQualityIntfControllerListener.h>

class CurrentAirQualityListener : public CurrentAirQualityIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint8_t m_contaminantType;
    double m_currentValue;
    double m_maxValue;
    double m_minValue;
    double m_precision;
    uint16_t m_updateMinTime;

    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_contaminantType = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_currentValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_maxValue = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        m_status = status;
        m_minValue = value;
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

    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_eventSignal.SetEvent();
    }

    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value)
    {
        m_eventSignal.SetEvent();
    }

    virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value)
    {
        m_eventSignal.SetEvent();
    }

    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value)
    {
        m_eventSignal.SetEvent();
    }

    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision)
    {
        m_eventSignal.SetEvent();
    }

    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime)
    {
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_CurrentAirQuality)
{
    WaitForControllee(CURRENT_AIR_QUALITY_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        CurrentAirQualityListener listener;
        HaeInterface* interface = m_controller->CreateInterface(CURRENT_AIR_QUALITY_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        CurrentAirQualityIntfController* controller = static_cast<CurrentAirQualityIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the ContaminantType property.");
            status = controller->GetContaminantType();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            EXPECT_EQ(listener.m_status, ER_OK);
            listener.m_event.ResetEvent();

            TEST_LOG_2("Retrieve the CurrentValue property.");
            status = controller->GetCurrentValue();
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

            TEST_LOG_2("Retrieve the MinValue property.");
            status = controller->GetMinValue();
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
