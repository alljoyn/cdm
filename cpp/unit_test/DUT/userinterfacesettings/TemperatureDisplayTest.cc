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
#include <algorithm>

#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllerListener.h>

class TemperatureDisplayListener : public TemperatureDisplayIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;

    uint8_t m_displayTemperatureUnit;
    uint8_t m_displayTemperatureUnitSignal;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    std::vector<uint8_t> m_supportedDisplayTemperatureUnits;
    std::vector<uint8_t> m_supportedDisplayTemperatureUnitsSignal;

    virtual void GetDisplayTemperatureUnitPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t temperatureUnit, void* context)
    {
        m_status = status;
        m_displayTemperatureUnit = temperatureUnit;
        m_event.SetEvent();
    }

    virtual void SetDisplayTemperatureUnitPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void GetSupportedDisplayTemperatureUnitsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& supportedDisplayTemperatureUnits, void* context)
    {
        m_supportedDisplayTemperatureUnits = supportedDisplayTemperatureUnits;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void DisplayTemperatureUnitPropertyChanged(const qcc::String& objectPath, const uint8_t temperatureUnit)
    {
        m_displayTemperatureUnitSignal = temperatureUnit;
        m_eventSignal.SetEvent();
    }

    virtual void SupportedDisplayTemperatureUnitsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& supportedDisplayTemperatureUnits)
    {
        m_supportedDisplayTemperatureUnitsSignal = supportedDisplayTemperatureUnits;
        m_eventSignal.SetEvent();
    }

    QStatus GetUnsupportedTemperatureUnit(uint8_t& unsupportedTemperatureUnit)
    {
        for(uint8_t i = 0; ; i++)
        {
            std::vector<uint8_t>::iterator it;
            it = std::find(m_supportedDisplayTemperatureUnits.begin(),m_supportedDisplayTemperatureUnits.end(), i);
            if(it == m_supportedDisplayTemperatureUnits.end())
            {
                unsupportedTemperatureUnit = i;
                return ER_OK;
            }
        }
        return ER_FAIL;
    }
};

TEST_F(CDMTest, CDM_v1_TemperatureDisplay)
{
    WaitForControllee(TEMPERATURE_DISPLAY_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        TemperatureDisplayListener listener;
        CdmInterface* interface = m_controller->CreateInterface(TEMPERATURE_DISPLAY_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        TemperatureDisplayIntfController* controller = static_cast<TemperatureDisplayIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the DisplayTemperatureUnit property.");
            status = controller->GetDisplayTemperatureUnit();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve SupportedDisplayTemperatureUnits property.");
            status = controller->GetSupportedDisplayTemperatureUnits();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        const uint8_t initDisplayTemperatureUnit = listener.m_supportedDisplayTemperatureUnits[0];
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the DisplayTemperatureUnit property to the 1st item of the SupportedDisplayTemperatureUnits.");
            if (listener.m_displayTemperatureUnit != initDisplayTemperatureUnit) {
                status = controller->SetDisplayTemperatureUnit(initDisplayTemperatureUnit);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_displayTemperatureUnitSignal, initDisplayTemperatureUnit);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the DisplayTemperatureUnit property to value outside SupportedDisplayTemperatureUnits.");
            uint8_t unsupportedTemperatureUnit = 0;
            status = listener.GetUnsupportedTemperatureUnit(unsupportedTemperatureUnit);
            if(status == ER_OK)
            {
                status = controller->SetDisplayTemperatureUnit(unsupportedTemperatureUnit);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_NE(listener.m_status, ER_OK);

                TEST_LOG_2("Get the DisplayTemperatureUnit property.");
                status = controller->GetDisplayTemperatureUnit();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_displayTemperatureUnit, initDisplayTemperatureUnit);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If DisplayTemperatureUnit > 1, set the TargetLevel property to the 2nd item of the SupportedDisplayTemperatureUnits.");
            if (listener.m_supportedDisplayTemperatureUnits.size() > 1) {
                const uint8_t validDisplayTemperatureUnit = listener.m_supportedDisplayTemperatureUnits[1];
                status = controller->SetDisplayTemperatureUnit(validDisplayTemperatureUnit);

                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the DisplayTemperatureUnit property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_displayTemperatureUnitSignal, validDisplayTemperatureUnit);

                TEST_LOG_3("Get the DisplayTemperatureUnit property.");
                status = controller->GetDisplayTemperatureUnit();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_displayTemperatureUnit, validDisplayTemperatureUnit);
            }
        }
    }
}