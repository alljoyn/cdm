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

#include <alljoyn/hae/interfaces/operation/AirRecirculationModeIntfController.h>
#include <alljoyn/hae/interfaces/operation/AirRecirculationModeIntfControllerListener.h>

class AirRecirculationModeListener : public AirRecirculationModeIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    bool m_isRecirculating;
    bool m_isRecirculatingSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context)
    {
        m_status = status;
        m_isRecirculating = isRecirculating;
        m_event.SetEvent();
    }

    virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating)
    {
        m_isRecirculatingSignal = isRecirculating;
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_02)
{
    WaitForControllee(AIR_RECIRCULATION_MODE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        AirRecirculationModeListener listener;
        HaeInterface* interface = m_controller->CreateInterface(AIR_RECIRCULATION_MODE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        AirRecirculationModeIntfController* controller = static_cast<AirRecirculationModeIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties")
        {
            TEST_LOG_2("Retrieve the IsRecirculating property.")
            status = controller->GetIsRecirculating();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        const bool initIsRecirculating = true;
        TEST_LOG_1("Initialize all read-write properties.")
        {
            TEST_LOG_2("Initialize the IsRecirculating property to true.")
            if (listener.m_isRecirculating != initIsRecirculating) {
                status = controller->SetIsRecirculating(initIsRecirculating);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_isRecirculatingSignal, initIsRecirculating);
            }
        }

        TEST_LOG_1("Set properties to valid value")
        {
            TEST_LOG_2("Set the IsRecirculating property to false.")
            {
                const bool validIsRecirculating = false;
                status = controller->SetIsRecirculating(validIsRecirculating);
                EXPECT_EQ(status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the IsRecirculating property.")
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_isRecirculatingSignal, validIsRecirculating);

                TEST_LOG_3("Get the IsRecirculating property.")
                status = controller->GetIsRecirculating();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_isRecirculating, validIsRecirculating);
            }
        }
    }
}
