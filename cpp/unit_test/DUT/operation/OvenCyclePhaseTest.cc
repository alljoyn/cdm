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

#include <interfaces/controller/operation/OvenCyclePhaseIntfController.h>
#include <interfaces/controller/operation/OvenCyclePhaseIntfControllerListener.h>
using namespace std;
class OvenCyclePhaseListener : public OvenCyclePhaseIntfControllerListener
{
public:
    typedef std::vector<uint8_t> SupportedCyclePhases;
    typedef std::vector<OvenCyclePhaseInterface::CyclePhaseDescriptor> CyclePhaseDescriptions;

    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;
    uint8_t m_cyclePhase;
    SupportedCyclePhases m_supportedCyclePhases;
    uint8_t m_cyclePhaseSignal;
    SupportedCyclePhases m_supportedCyclePhasesSignal;
    CyclePhaseDescriptions m_phasesDescriptions;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t cyclePhase, void* context) override
    {
        m_cyclePhase = cyclePhase;
        m_status = status;
        m_event.SetEvent();
    }


    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const SupportedCyclePhases& listOfCyclePhases, void* context) override
    {
        m_supportedCyclePhases = listOfCyclePhases;
        m_status = status;
        m_event.SetEvent();
    }


    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase) override
    {
        m_cyclePhaseSignal = cyclePhase;
        m_eventSignal.SetEvent();
    }


    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const SupportedCyclePhases& listOfCyclePhases) override
    {
        m_supportedCyclePhasesSignal = listOfCyclePhases;
        m_eventSignal.SetEvent();
    }


    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const CyclePhaseDescriptions& listOfCycleDescriptions,
                                                      void* context, const char* errorName, const char* errorMessage) override
    {
        m_phasesDescriptions = listOfCycleDescriptions;
        m_status = status;
        if (status != ER_OK) {
            if (errorName) {
                m_errorName = errorName;
            }
            if (errorMessage) {
                m_errorMessage = errorMessage;
            }
        }
        m_event.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_OvenCyclePhase)
{
    WaitForControllee(OVEN_CYCLE_PHASE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<OvenCyclePhaseListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.OvenCyclePhase", m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<OvenCyclePhaseIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the CyclePhase property.");
            status = controller->GetCyclePhase();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedCyclePhases property.");
            status = controller->GetSupportedCyclePhases();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }

        TEST_LOG_1("Call method with invalid param.");
        {
            TEST_LOG_2("Call GetVendorPhasesDescription method with \"Invalid_lang\".");
            qcc::String invalidLang = "Invalid_lang";
            status = controller->GetVendorPhasesDescription(invalidLang);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_NE(listener->m_status, ER_OK);
            EXPECT_STREQ(listener->m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(LANGUAGE_NOT_SUPPORTED).c_str());
        }

        TEST_LOG_1("Call method with valid param.");
        {
            TEST_LOG_2("Call GetVendorPhasesDescription method with \"en\".");
            qcc::String validLang = "en";
            status = controller->GetVendorPhasesDescription(validLang);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }
    }
}