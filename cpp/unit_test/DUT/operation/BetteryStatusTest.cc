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

#include <alljoyn/hae/interfaces/operation/BatteryStatusIntfController.h>
#include <alljoyn/hae/interfaces/operation/BatteryStatusIntfControllerListener.h>

class BatteryStatusListener : public BatteryStatusIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_currentValue;
    bool m_isCharging;
    uint8_t m_currentValueSignal;
    bool m_isChargingSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t currentValue, void* context)
    {
        m_status = status;
        m_currentValue = currentValue;
        m_event.SetEvent();
    }

    virtual void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool isCharging, void* context)
    {
        m_status = status;
        m_isCharging = isCharging;
        m_event.SetEvent();
    }

    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t currentValue)
    {
        m_currentValueSignal = currentValue;
        m_eventSignal.SetEvent();
    }

    virtual void OnIsChargingChanged(const qcc::String& objectPath, const bool isCharging)
    {
        m_isChargingSignal = isCharging;
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_BatteryStatus)
{
    WaitForControllee(BATTERY_STATUS_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        BatteryStatusListener listener;
        HaeInterface* interface = m_controller->CreateInterface(BATTERY_STATUS_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        BatteryStatusIntfController* controller = static_cast<BatteryStatusIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the CurrentValue property.");
            status = controller->GetCurrentValue();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the IsCharging property.");
            status = controller->GetIsCharging();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}
