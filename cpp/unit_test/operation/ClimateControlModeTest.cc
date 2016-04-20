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

#include <alljoyn/hae/interfaces/operation/ClimateControlModeIntfController.h>
#include <alljoyn/hae/interfaces/operation/ClimateControlModeIntfControllerListener.h>

class ClimateControlModeListener : public ClimateControlModeIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint16_t m_mode;
    SupportedModes m_supportedModes;
    uint16_t m_operationalState;
    uint16_t m_modeSignal;
    SupportedModes m_supportedModesSignal;
    uint16_t m_operationalStateSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        m_status = status;
        m_mode = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context)
    {
        m_status = status;
        m_supportedModes = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        m_status = status;
        m_operationalState = value;
        m_event.SetEvent();
    }

    virtual void OnModeChanged(const qcc::String& objectPath, const uint16_t value)
    {
        m_modeSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value)
    {
        m_supportedModesSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const uint16_t value)
    {
        m_operationalStateSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_07)
{
    WaitForControllee(CLIMATE_CONTROL_MODE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        ClimateControlModeListener listener;
        HaeInterface* interface = m_controller->CreateInterface(CLIMATE_CONTROL_MODE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        ClimateControlModeIntfController* controller = static_cast<ClimateControlModeIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.")
        {
            TEST_LOG_2("Retrieve the Mode property.")
            status = controller->GetMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedModes property.")
            status = controller->GetSupportedModes();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the OperationalState property.")
            status = controller->GetOperationalState();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        const uint16_t initMode = listener.m_supportedModes[0];
        TEST_LOG_1("Initialize all read-write properties.")
        {
            TEST_LOG_2("Set the Mode property to the 1st item of SupportedModes.")
            if (listener.m_mode != initMode) {
                status = controller->SetMode(initMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_modeSignal, initMode);
            }
        }

        TEST_LOG_1("Set properties to invalid value.")
        {
            TEST_LOG_2("Set the Mode property to 0xFF(not supported).")
            {
                const uint8_t notSupportedMode = 0xff;
                status = controller->SetMode(notSupportedMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_3("Get the Mode property.")
                status = controller->GetMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_mode, initMode);
            }

        }
        TEST_LOG_1("Set properties to valid value.")
        {
            TEST_LOG_2("If size of SupportedModes > 1, set the Mode property to the 2nd item of the SupportedModes.")
            if (listener.m_supportedModes.size() > 1) {
                uint16_t validMode = listener.m_supportedModes[1];
                status = controller->SetMode(validMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Mode property.")
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_modeSignal, validMode);

                TEST_LOG_3("Get the Mode property")
                status = controller->GetMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_mode, validMode);
            }
        }
    }
}
