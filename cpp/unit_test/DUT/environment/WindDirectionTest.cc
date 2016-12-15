/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <interfaces/controller/environment/WindDirectionIntfController.h>
#include <interfaces/controller/environment/WindDirectionIntfControllerListener.h>

class WindDirectionListener : public WindDirectionIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;

    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    uint16_t m_horizontalDirection;
    uint16_t m_horizontalMax;
    uint8_t  m_horizontalAutoMode;
    uint16_t m_verticalDirection;
    uint16_t m_verticalMax;
    uint8_t  m_verticalAutoMode;
    uint16_t m_horizontalDirectionSignal;
    uint16_t m_horizontalMaxSignal;
    uint8_t  m_horizontalAutoModeSignal;
    uint16_t m_verticalDirectionSignal;
    uint16_t m_verticalMaxSignal;
    uint8_t  m_verticalAutoModeSignal;

    virtual void OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value) override
    {
        m_horizontalDirectionSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value) override
    {
        m_horizontalMaxSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnHorizontalAutoModeChanged(const qcc::String& objectPath, const WindDirectionInterface::AutoMode value) override
    {
        m_horizontalAutoModeSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value) override
    {
        m_verticalDirectionSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value) override
    {
        m_verticalMaxSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnVerticalAutoModeChanged(const qcc::String& objectPath, const WindDirectionInterface::AutoMode value) override
    {
        m_verticalAutoModeSignal = value;
        m_eventSignal.SetEvent();
    }

    virtual void OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
    {
        m_status = status;
        m_horizontalDirection = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
    {
        m_status = status;
        m_horizontalMax= value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const WindDirectionInterface::AutoMode value, void* context) override
    {
        m_status = status;
        m_horizontalAutoMode = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
    {
        m_status = status;
        m_verticalDirection = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
    {
        m_status = status;
        m_verticalMax = value;
        m_event.SetEvent();
    }

    virtual void OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const WindDirectionInterface::AutoMode value, void* context) override
    {
        m_status = status;
        m_verticalAutoMode = value;
        m_event.SetEvent();
    }

    virtual void OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_WindDirection)
{
    WaitForControllee(WIND_DIRECTION_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {

        auto listener = mkRef<WindDirectionListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Environment.WaterLevel", m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);

        auto controller = std::dynamic_pointer_cast<WindDirectionIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the HorizontalDirection property.");
            status = controller->GetHorizontalDirection();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the HorizontalMax property.");
            status = controller->GetHorizontalMax();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the HorizontalAutoMode property.");
            status = controller->GetHorizontalAutoMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the VerticalDirection property.");
            status = controller->GetVerticalDirection();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the VerticalMax property.");
            status = controller->GetVerticalMax();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_2("Retrieve the VerticalAutoMode property.");
            status = controller->GetVerticalAutoMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();
        }

        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the HorizontalDirection property to 0.");
            if (listener->m_horizontalDirection != 0) {
                status =  controller->SetHorizontalDirection(0);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_horizontalDirectionSignal, 0);
            }

            TEST_LOG_2("Initialize the HorizontalAutoMode property to 0(Off).");
            if (listener->m_horizontalAutoMode != WindDirectionInterface::AUTO_MODE_OFF) {
                status =  controller->SetHorizontalAutoMode(WindDirectionInterface::AUTO_MODE_OFF);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_horizontalAutoModeSignal, WindDirectionInterface::AUTO_MODE_OFF);
            }

            TEST_LOG_2("Initialize the VerticalDirection property to 0.");
            if (listener->m_verticalDirection != 0) {
                status =  controller->SetVerticalDirection(0);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_verticalDirectionSignal, 0);
            }

            TEST_LOG_2("Initialize the VerticalAutoMode property to 0(Off).");
            if (listener->m_verticalAutoMode != WindDirectionInterface::AUTO_MODE_OFF) {
                status =  controller->SetVerticalAutoMode(WindDirectionInterface::AUTO_MODE_OFF);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_verticalAutoModeSignal, WindDirectionInterface::AUTO_MODE_OFF);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("Set the HorizontalDirection property to 1.");
            status =  controller->SetHorizontalDirection(1);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the HorizontalDirection property.");
            EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
            listener->m_eventSignal.ResetEvent();
            EXPECT_EQ(listener->m_horizontalDirectionSignal, 1);

            TEST_LOG_3("Get the HorizontalDirection property.");
            status =  controller->GetHorizontalDirection();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_EQ(listener->m_horizontalDirection, 1);

            TEST_LOG_2("If HorizontalMax != 1, Set the HorizontalDirection property to HorizontalMax.");
            if (listener->m_horizontalMax != 1) {
                status =  controller->SetHorizontalDirection(listener->m_horizontalMax);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the HorizontalDirection property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_horizontalDirectionSignal, listener->m_horizontalMax);

                TEST_LOG_3("Get the HorizontalDirection property.");
                status =  controller->GetHorizontalDirection();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_horizontalDirection, listener->m_horizontalMax);
            }

            TEST_LOG_2("If HorizontalAutoMode != 0xFF, Set HorizontalAutoMode property to 1(On).");
            if (listener->m_horizontalAutoMode != WindDirectionInterface::AUTO_MODE_NOT_SUPPORTED) {
                status =  controller->SetHorizontalAutoMode(WindDirectionInterface::AUTO_MODE_ON);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the HorizontalAutoMode property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_horizontalAutoModeSignal, WindDirectionInterface::AUTO_MODE_ON);

                TEST_LOG_3("Get the HorizontalAutoMode property.");
                status =  controller->GetHorizontalAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_horizontalAutoMode, WindDirectionInterface::AUTO_MODE_ON);
            }

            TEST_LOG_2("Set the VerticalDirection property to 1.");
            status =  controller->SetVerticalDirection(1);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_3("Wait the PropertiesChanged signal for the VerticalDirection property.");
            EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
            listener->m_eventSignal.ResetEvent();
            EXPECT_EQ(listener->m_verticalDirectionSignal, 1);

            TEST_LOG_3("Get the VerticalDirection property.");
            status =  controller->GetVerticalDirection();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_EQ(listener->m_verticalDirection, 1);

            TEST_LOG_2("If VerticalMax != 1, Set the VerticalDirection property to VerticalMax.");
            if (listener->m_verticalMax != 1) {
                status =  controller->SetVerticalDirection(listener->m_verticalMax);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the VerticalDirection property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_verticalDirectionSignal, listener->m_verticalMax);

                TEST_LOG_3("Get the VerticalDirection property.");
                status =  controller->GetVerticalDirection();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_verticalDirection, listener->m_verticalMax);
            }

            TEST_LOG_2("If VerticalAutoMode != 0xFF, Set VerticalAutoMode property to 1(On).");
            if (listener->m_verticalAutoMode != WindDirectionInterface::AUTO_MODE_NOT_SUPPORTED) {
                status =  controller->SetVerticalAutoMode(WindDirectionInterface::AUTO_MODE_ON);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                EXPECT_EQ(listener->m_status, ER_OK);
                listener->m_event.ResetEvent();

                TEST_LOG_3("Wait the PropertiesChanged signal for the VerticalAutoMode property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_verticalAutoModeSignal, WindDirectionInterface::AUTO_MODE_ON);

                TEST_LOG_3("Get the VerticalAutoMode property.");
                status =  controller->GetVerticalAutoMode();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_verticalAutoMode, WindDirectionInterface::AUTO_MODE_ON);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        TEST_LOG_2("If HorizontalMax != UINT16_MAX, Set the HorizontalDirection property to HorizontalMax + 1.");
        if (listener->m_horizontalMax != UINT16_MAX) {
            status =  controller->SetHorizontalDirection(listener->m_horizontalMax + 1);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_3("Get the HorizontalDirection property.");
            status =  controller->GetHorizontalDirection();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_EQ(listener->m_horizontalDirection, listener->m_horizontalMax);
        }

        WindDirectionInterface::AutoMode invalidValue = (WindDirectionInterface::AutoMode)2;
        TEST_LOG_2("Set the HorizontalAutoMode property to 2.");
        status =  controller->SetHorizontalAutoMode(invalidValue);
        EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
        EXPECT_NE(listener->m_status, ER_OK);
        listener->m_event.ResetEvent();

        TEST_LOG_3("Get the HorizontalAutoMode property.");
        status =  controller->GetHorizontalAutoMode();
        EXPECT_EQ(status, ER_OK);
        EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
        listener->m_event.ResetEvent();
        EXPECT_EQ(listener->m_status, ER_OK);
        EXPECT_EQ(listener->m_horizontalAutoMode, WindDirectionInterface::AUTO_MODE_ON);

        TEST_LOG_2("If VerticalMax != UINT16_MAX, Set the VerticalDirection property to VerticalMax + 1.");
        if (listener->m_verticalMax != UINT16_MAX) {
            status =  controller->SetVerticalDirection(listener->m_verticalMax + 1);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            EXPECT_EQ(listener->m_status, ER_OK);
            listener->m_event.ResetEvent();

            TEST_LOG_3("Get the VerticalDirection property.");
            status =  controller->GetVerticalDirection();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_EQ(listener->m_verticalDirection, listener->m_verticalMax);
        }

        TEST_LOG_2("Set the VerticalAutoMode property to 2.");
        status =  controller->SetVerticalAutoMode(invalidValue);
        EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
        EXPECT_NE(listener->m_status, ER_OK);
        listener->m_event.ResetEvent();

        TEST_LOG_3("Get the VerticalAutoMode property.");
        status =  controller->GetVerticalAutoMode();
        EXPECT_EQ(status, ER_OK);
        EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
        listener->m_event.ResetEvent();
        EXPECT_EQ(listener->m_status, ER_OK);
        EXPECT_EQ(listener->m_verticalAutoMode, WindDirectionInterface::AUTO_MODE_ON);
    }
}