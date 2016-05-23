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

#include <alljoyn/hae/interfaces/operation/FanSpeedLevelIntfController.h>
#include <alljoyn/hae/interfaces/operation/FanSpeedLevelIntfControllerListener.h>

class FanSpeedLevelListener : public FanSpeedLevelIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_fanSpeedLevel;
    uint8_t m_maxFanSpeedLevel;
    uint8_t m_autoMode;
    uint8_t m_fanSpeedLevelSignal;
    uint8_t m_autoModeSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_fanSpeedLevel = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_maxFanSpeedLevel = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_autoMode = value;
        m_event.SetEvent();
    }

    virtual void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_fanSpeedLevelSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_autoModeSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_14)
{
    WaitForControllee(FAN_SPEED_LEVEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);
        FanSpeedLevelListener listener;
        HaeInterface* interface = m_controller->CreateInterface(FAN_SPEED_LEVEL_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        FanSpeedLevelIntfController* controller = static_cast<FanSpeedLevelIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retrieve the FanSpeedLevel property.");
            status = controller->GetFanSpeedLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the MaxFanSpeedLevel property.");
            status = controller->GetMaxFanSpeedLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the AutoMode property.");
            status = controller->GetAutoMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        TEST_LOG_1("Initialize all read-write properties");
        {
            TEST_LOG_2("Initialize the FanSpeedLevel property to 0x01.");
            if (listener.m_fanSpeedLevel != 0x01) {
                status = controller->SetFanSpeedLevel(0x01);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_fanSpeedLevelSignal, 0x01);
            }

            TEST_LOG_2("If AutoMode != 0xFF(not supported), set AutoMode property to 0x00(Off).");
            if (listener.m_autoMode != 0xFF && listener.m_autoMode != 0x00) {
                status = controller->SetAutoMode(0x00);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_autoModeSignal, 0x00);
            }
        }


        TEST_LOG_1("Set properties to invalid value.");
        {

            TEST_LOG_2("If MaxFanSpeedLevel != UINT8_MAX, set the FanSpeedLevel property to MaxFanSpeedLevel + 1");
            if (listener.m_maxFanSpeedLevel != UINT8_MAX) {
                uint8_t invalidValue = listener.m_maxFanSpeedLevel + 1;
                status = controller->SetFanSpeedLevel(invalidValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_3("Get the FanSpeedLevel property.");
                status = controller->GetFanSpeedLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_fanSpeedLevel, 0x01);
            }

            TEST_LOG_2("Set the FanSpeedLevel property to 0x00 (Off).");
            {
                status = controller->SetFanSpeedLevel(0x00);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_3("Get the FanSpeedLevel property.");
                status = controller->GetFanSpeedLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_fanSpeedLevel, 0x01);
            }

            TEST_LOG_2("Set the AutoMode property to 0xFF(not supported).");
            {
                uint8_t autoMode = listener.m_autoMode;
                status = controller->SetAutoMode(0xFF);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_3("Get the AutoMode property.");
                status = controller->GetAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                if (autoMode != 0xFF) {
                    EXPECT_EQ(listener.m_autoMode, 0x00);
                }
                else {
                    EXPECT_EQ(listener.m_autoMode, 0xFF);
                }
            }

            TEST_LOG_2("Set the AutoMode property to 0x02.");
            {
                uint8_t autoMode = listener.m_autoMode;
                status = controller->SetAutoMode(0x02);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_3("Get the AutoMode property.");
                status = controller->GetAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                if (autoMode != 0xFF) {
                    EXPECT_EQ(listener.m_autoMode, 0x00);
                }
                else {
                    EXPECT_EQ(listener.m_autoMode, 0xFF);
                }
            }
        }


        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If MaxFanSpeedLevel > 1, set the FanSpeedLevel property to 2.");
            if (listener.m_maxFanSpeedLevel > 1) {
                uint8_t validFanSpeedLevel = 2;
                status = controller->SetFanSpeedLevel(validFanSpeedLevel);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the FanSpeedLevel property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_fanSpeedLevelSignal, validFanSpeedLevel);

                TEST_LOG_3("Get the FanSpeedLevel property.");
                status = controller->GetFanSpeedLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_fanSpeedLevel, validFanSpeedLevel);
            }

            TEST_LOG_2("If AutoMode != 0xFF, set the AutoMode property to 0x01.");
            if (listener.m_autoMode != 0xFF) {
                uint8_t validAutoMode = 0x01;
                status = controller->SetAutoMode(validAutoMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the AutoMode property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_autoModeSignal, validAutoMode);

                TEST_LOG_3("Get the AutoMode property.");
                status = controller->GetAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_autoMode, validAutoMode);
            }
        }
    }
}
