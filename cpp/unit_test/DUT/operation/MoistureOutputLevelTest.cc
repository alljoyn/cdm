/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllerListener.h>

class MoistureOutputLevelListener : public MoistureOutputLevelIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_moistureOutputLevel;
    uint8_t m_maxMoistureOutputLevel;
    uint8_t m_autoMode;
    uint8_t m_moistureOutputLevelSignal;
    uint8_t m_maxMoistureOutputLevelSignal;
    uint8_t m_autoModeSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_moistureOutputLevel = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        m_status = status;
        m_maxMoistureOutputLevel = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t autoMode, void* context)
    {
        m_status = status;
        m_autoMode = autoMode;
        m_event.SetEvent();
    }

    virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_moistureOutputLevelSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        m_maxMoistureOutputLevel = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t autoMode)
    {
        m_autoModeSignal = autoMode;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_MoistureOutputLevel)
{
    WaitForControllee(MOISTURE_OUTPUT_LEVEL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        MoistureOutputLevelListener listener;
        CdmInterface* interface = m_controller->CreateInterface(MOISTURE_OUTPUT_LEVEL_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        MoistureOutputLevelIntfController* controller = static_cast<MoistureOutputLevelIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retrieve the MoistureOutputLevel property.");
            status = controller->GetMoistureOutputLevel();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the MaxMoistureOutputLevel property.");
            status = controller->GetMaxMoistureOutputLevel();
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

        const uint8_t initMoistureOutputLevel = 0;
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the MoistureOutputLevel property to 0.");
            if (listener.m_moistureOutputLevel != initMoistureOutputLevel) {
                status = controller->SetMoistureOutputLevel(initMoistureOutputLevel);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_moistureOutputLevelSignal, initMoistureOutputLevel);
            }

            TEST_LOG_2("Initialize the AutoMode property to 0(Off).");
            if (listener.m_autoMode != MoistureOutputLevelInterface::OFF) {
                status =  controller->SetAutoMode(MoistureOutputLevelInterface::OFF);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_autoModeSignal, MoistureOutputLevelInterface::OFF);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("If MaxMoistureOutputLevel != UINT8_MAX, Set the MoistureOutputLevel property to MaxMoistureOutputLevel + 1.");
            if (listener.m_maxMoistureOutputLevel != UINT8_MAX) {
                const uint16_t invalidMoistureOutputLevel = listener.m_maxMoistureOutputLevel + 1;
                status = controller->SetMoistureOutputLevel(invalidMoistureOutputLevel);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_3("Get the MoistureOutputLevel property.");
                status = controller->GetMoistureOutputLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_moistureOutputLevel, initMoistureOutputLevel);

                uint8_t invalidValue = 2;
                TEST_LOG_2("Set the AutoMode property to 2.");
                status =  controller->SetAutoMode(invalidValue);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_NE(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                TEST_LOG_3("Get the AutoMode property.");
                status =  controller->GetAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_autoMode, MoistureOutputLevelInterface::OFF);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If MaxMoistureOutputLevel >= 1, Set the MoistureOutputLevel property to value 1.");
            if (listener.m_maxMoistureOutputLevel >= 1) {
                const uint8_t validValue = 1;
                status = controller->SetMoistureOutputLevel(validValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the MoistureOutputLevel property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_moistureOutputLevelSignal, validValue);

                TEST_LOG_3("Get the MoistureOutputLevel property.");
                status = controller->GetMoistureOutputLevel();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_moistureOutputLevel, validValue);
            }

            TEST_LOG_2("If AutoMode != 0xFF, Set AutoMode property to 1(On).");
            if (listener.m_autoMode != MoistureOutputLevelInterface::NOT_SUPPORTED) {
                status = controller->SetAutoMode(MoistureOutputLevelInterface::ON);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                EXPECT_EQ(listener.m_status, ER_OK);
                listener.m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the AutoMode property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_autoModeSignal, MoistureOutputLevelInterface::ON);

                TEST_LOG_3("Get the AutoMode property.");
                status = controller->GetAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_autoMode, MoistureOutputLevelInterface::ON);
            }
        }
    }
}