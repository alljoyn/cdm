/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllerListener.h>

class RobotCleaningCyclePhaseListener : public RobotCleaningCyclePhaseIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_cyclePhase;
    RobotCleaningCyclePhaseInterface::SupportedCyclePhases m_supportedCyclePhases;
    uint8_t m_cyclePhaseSignal;
    RobotCleaningCyclePhaseInterface::SupportedCyclePhases m_supportedCyclePhasesSignal;
    RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors m_phasesDescriptions;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t cyclePhase, void* context)
    {
        m_errorName = "";
        m_errorMessage = "";

        m_cyclePhase = cyclePhase;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath,
                                                   const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases, void* context)
    {
        m_errorName = "";
        m_errorMessage = "";

        m_supportedCyclePhases = supportedCyclePhases;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath,
                                                      const RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription, void* context,
                                                      const char* errorName, const char* errorMessage)
    {
        if (status != ER_OK) {
            if (errorName) {
                m_errorName = errorName;
            }
            if (errorMessage) {
                m_errorMessage = errorMessage;
            }
        }
         m_phasesDescriptions = phasesDescription;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase)
    {
        m_cyclePhaseSignal = cyclePhase;
        m_eventSignal.SetEvent();
    }

    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath,
                                               const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases)
    {
        m_supportedCyclePhasesSignal = supportedCyclePhases;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_RobotCleaningCyclePhase)
{
    WaitForControllee(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        RobotCleaningCyclePhaseListener listener;
        CdmInterface* interface = m_controller->CreateInterface(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        RobotCleaningCyclePhaseIntfController* controller = static_cast<RobotCleaningCyclePhaseIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the CyclePhase property.");
            status = controller->GetCyclePhase();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedCyclePhases property.");
            status = controller->GetSupportedCyclePhases();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        TEST_LOG_1("Call method with invalid param.");
        {
            TEST_LOG_2("Call GetVendorPhasesDescription method with \"Invalid_lang\".");
            qcc::String invalidLang = "Invalid_lang";
            status = controller->GetVendorPhasesDescription(invalidLang);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);
            EXPECT_STREQ(listener.m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(LANGUAGE_NOT_SUPPORTED).c_str());
        }

        TEST_LOG_1("Call method with valid param.");
        {
            TEST_LOG_2("Call GetVendorPhasesDescription method with \"en\".");
            qcc::String validLang = "en";
            status = controller->GetVendorPhasesDescription(validLang);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}