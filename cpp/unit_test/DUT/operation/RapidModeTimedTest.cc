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

#include "CdmTest.h"

#include <interfaces/controller/operation/RapidModeTimedIntfController.h>
#include <interfaces/controller/operation/RapidModeTimedIntfControllerListener.h>

class RapidModeTimedListener : public RapidModeTimedIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint16_t m_rapidModeMinutesRemaining;
    uint16_t m_maxSetMinutes;
    uint16_t m_rapidModeMinutesRemainingSignal;

    virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        m_status = status;
        m_rapidModeMinutesRemaining = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        m_status = status;
        m_maxSetMinutes = value;
        m_event.SetEvent();
    }

    virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value)
    {
        m_rapidModeMinutesRemainingSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_RapidModeTimed)
{
    WaitForControllee(RAPID_MODE_TIMED_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<RapidModeTimedListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.RapidModeTimed", m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<RapidModeTimedIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retieve the RapidModeMinutesRemaining property.");
            status = controller->GetRapidModeMinutesRemaining();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retieve the MaxSetMinutes property.");
            status = controller->GetMaxSetMinutes();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }

        const uint16_t initValue = 0;
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the RapidModeMinutesRemaining property to 0.");
            if (listener->m_rapidModeMinutesRemaining != initValue) {
                status = controller->SetRapidModeMinutesRemaining(initValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT));
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_rapidModeMinutesRemainingSignal, initValue);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("If MaxSetMinutes != UINT16_MAX, Set the RapidModeMinutesRemaining property to MaxSetMinutes + 1.");
            if (listener->m_maxSetMinutes != UINT16_MAX) {
                const uint32_t invalidValue = listener->m_maxSetMinutes + 1;
                status = controller->SetRapidModeMinutesRemaining(invalidValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_NE(listener->m_status, ER_OK);

                TEST_LOG_3("Get the RapidModeMinutesRemaining property.");
                status = controller->GetRapidModeMinutesRemaining();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_rapidModeMinutesRemaining, initValue);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If MaxSetMinutes >= 1, Set the RapidModeMinutesRemaining property to value 1.");
            if (listener->m_maxSetMinutes >= 1)
            {
                const uint16_t validValue = 1;
                status = controller->SetRapidModeMinutesRemaining(validValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the RapidModeMinutesRemaining property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT));
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_rapidModeMinutesRemainingSignal, validValue);

                TEST_LOG_3("Get the RapidModeMinutesRemaining property.");
                status = controller->GetRapidModeMinutesRemaining();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_rapidModeMinutesRemaining, validValue);
            }
        }
    }
}
