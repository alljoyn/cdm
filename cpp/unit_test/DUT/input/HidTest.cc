/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "CdmTest.h"

#include <alljoyn/cdm/interfaces/input/HidIntfController.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControllerListener.h>

class HidListener : public HidIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    HidInterface::SupportedInputEvents m_supportedEvents;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents,
                                              void* context)
    {
        m_status = status;
        m_supportedEvents = supportedEvents;
        m_event.SetEvent();
    }

    virtual void OnSupportedEventsChanged(const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents)
    {
        m_supportedEvents = supportedEvents;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_Hid)
{
    WaitForControllee (HID_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);
        HidListener listener;
        CdmInterface* interface = m_controller->CreateInterface(HID_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                m_interfaces[i].sessionId, listener);
        HidIntfController* controller = static_cast<HidIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            status = controller->GetSupportedEvents();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        TEST_LOG_1("Call method");
        {
            TEST_LOG_2("If size of SupportedEvents > 1, Call the InjectEvents method with 1st item of SupportedInputEvents.");
            if (listener.m_supportedEvents.size() > 1) {
                HidInterface::SupportedInputEvent& firstItem = listener.m_supportedEvents[0];
                HidInterface::InputEvents events;
                HidInterface::InputEvent event;

                event.type = firstItem.type;
                event.code = firstItem.code;
                event.value = 1;
                events.push_back(event);
                status = controller->InjectEvents(events);
                EXPECT_EQ(status, ER_OK);
            }
        }
    }
}