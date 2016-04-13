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

#include <alljoyn/hae/interfaces/operation/EnergyUsageIntfController.h>
#include <alljoyn/hae/interfaces/operation/EnergyUsageIntfControllerListener.h>

class EnergyUsageListener : public EnergyUsageIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    double m_cumulativeEnergy;
    double m_precision;
    uint16_t m_updateMinTime;
    double m_cumulativeEnergySignal;
    double m_precisionSignal;
    uint16_t m_updateMinTimeSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double cumulativeEnergy, void* context)
    {
        m_status = status;
        m_cumulativeEnergy = cumulativeEnergy;
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

    virtual void OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
    {
        m_status = status;
        m_errorName = errorName;
        m_errorMessage = errorMessage;
        m_event.SetEvent();
    }

    virtual void OnCumulativeEnergyChanged(const qcc::String& objectPath, const double cumulativeEnergy)
    {
        m_cumulativeEnergySignal = cumulativeEnergy;
        m_eventSignal.SetEvent();
    }

    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision)
    {
        m_precisionSignal = precision;
        m_eventSignal.SetEvent();
    }

    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime)
    {
        m_updateMinTimeSignal = updateMinTime;
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_13)
{
    WaitForControllee(ENERGY_USAGE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);
        EnergyUsageListener listener;
        HaeInterface* interface = m_controller->CreateInterface(ENERGY_USAGE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        EnergyUsageIntfController* controller = static_cast<EnergyUsageIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retrieve the CumulativeEnergy property.");
            status = controller->GetCumulativeEnergy();
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

        TEST_LOG_1("Call method");
        {
            TEST_LOG_2("Call the ResetCumulativeEnergy method");
            {
                status = controller->ResetCumulativeEnergy();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("CumulativeEnergy != 0.0, wait the PropertiesChanged signal for the ResetCumulativeEnergy property");
                double cumulativeEnergy = 0.0;
                if (listener.m_cumulativeEnergy != cumulativeEnergy) {
                    EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                    listener.m_eventSignal.ResetEvent();
                    EXPECT_DOUBLE_EQ(listener.m_cumulativeEnergySignal, cumulativeEnergy);
                }

                TEST_LOG_3("Get the ResetCumulativeEnergy property");
                status = controller->GetCumulativeEnergy();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_DOUBLE_EQ(listener.m_cumulativeEnergy, cumulativeEnergy);
            }
        }
    }
}
