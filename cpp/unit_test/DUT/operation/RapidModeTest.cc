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

#include <interfaces/controller/operation/RapidModeIntfController.h>
#include <interfaces/controller/operation/RapidModeIntfControllerListener.h>

class RapidModeListener : public RapidModeIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;
    bool m_rapidMode;
    bool m_rapidModeSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;


    virtual void OnSetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnGetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, const bool rapidMode, void* context)
    {
        m_status = status;
        m_rapidMode = rapidMode;
        m_event.SetEvent();
    }

    virtual void RapidModePropertyChanged(const qcc::String& objectPath, const bool rapidMode)
    {
        m_rapidModeSignal = rapidMode;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_RapidMode)
{
    WaitForControllee(RAPID_MODE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<RapidModeListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.RapidMode", m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<RapidModeIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the RapidMode property.");
            status = controller->GetRapidMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }

        const bool initRapidMode = false;;
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the RapidMode property to false.");
            if (listener->m_rapidMode != initRapidMode) {
                status = controller->SetRapidMode(initRapidMode);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_rapidModeSignal, initRapidMode);
            }
        }
        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("Set the RapidMode property to true.");
            status = controller->SetRapidMode(true);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_3("Wait the PropertiesChanged signal for the RapidMode property.");
            EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
            listener->m_eventSignal.ResetEvent();
            EXPECT_TRUE(listener->m_rapidModeSignal);

            TEST_LOG_3("Get the RapidMode property.");
            status = controller->GetRapidMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_TRUE(listener->m_rapidMode);
        }


    }
}
