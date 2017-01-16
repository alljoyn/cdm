/******************************************************************************
 * 
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 * 
 *    SPDX-License-Identifier: Apache-2.0
 * 
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include <interfaces/controller/operation/ClimateControlModeIntfController.h>
#include <interfaces/controller/operation/ClimateControlModeIntfControllerListener.h>

class ClimateControlModeListener : public ClimateControlModeIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;
    ClimateControlModeInterface::Mode m_mode;
    std::vector<ClimateControlModeInterface::Mode> m_supportedModes;
    ClimateControlModeInterface::OperationalState m_operationalState;
    ClimateControlModeInterface::Mode m_modeSignal;
    std::vector<ClimateControlModeInterface::Mode> m_supportedModesSignal;
    ClimateControlModeInterface::OperationalState m_operationalStateSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const ClimateControlModeInterface::Mode value, void* context) override
    {
        m_status = status;
        m_mode = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<ClimateControlModeInterface::Mode>& value, void* context) override
    {
        m_status = status;
        m_supportedModes = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const ClimateControlModeInterface::OperationalState value, void* context) override
    {
        m_status = status;
        m_operationalState = value;
        m_event.SetEvent();
    }

    virtual void OnModeChanged(const qcc::String& objectPath, const ClimateControlModeInterface::Mode value) override
    {
        m_modeSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<ClimateControlModeInterface::Mode>& value) override
    {
        m_supportedModesSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const ClimateControlModeInterface::OperationalState value) override
    {
        m_operationalStateSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_ClimateControlMode)
{
    WaitForControllee(CLIMATE_CONTROL_MODE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<ClimateControlModeListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.ClimateControlMode", m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<ClimateControlModeIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the Mode property.");
            status = controller->GetMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedModes property.");
            status = controller->GetSupportedModes();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the OperationalState property.");
            status = controller->GetOperationalState();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }

        const auto initMode = listener->m_supportedModes[0];
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the Mode property to the 1st item of SupportedModes.");
            if (listener->m_mode != initMode) {
                status = controller->SetMode(initMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_modeSignal, initMode);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the Mode property to 0xFF(not supported).");
            {
                auto notSupportedMode = (ClimateControlModeInterface::Mode)0xff;
                status = controller->SetMode(notSupportedMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_NE(listener->m_status, ER_OK);

                TEST_LOG_3("Get the Mode property.");
                status = controller->GetMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_mode, initMode);
            }

        }
        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If size of SupportedModes > 1, set the Mode property to the 2nd item of the SupportedModes.");
            if (listener->m_supportedModes.size() > 1) {
                const auto validMode = listener->m_supportedModes[1];
                status = controller->SetMode(validMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Mode property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_modeSignal, validMode);

                TEST_LOG_3("Get the Mode property");
                status = controller->GetMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_mode, validMode);
            }
        }
    }
}
