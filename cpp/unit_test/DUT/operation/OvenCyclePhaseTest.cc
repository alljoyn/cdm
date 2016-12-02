/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include "CdmTest.h"

#include <alljoyn/cdm/interfaces/operation/OvenCyclePhaseIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OvenCyclePhaseIntfControllerListener.h>
using namespace std;
class OvenCyclePhaseListener : public OvenCyclePhaseIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_cyclePhase;
    OvenCyclePhaseInterface::SupportedCyclePhases m_supportedCyclePhases;
    uint8_t m_cyclePhaseSignal;
    OvenCyclePhaseInterface::SupportedCyclePhases m_supportedCyclePhasesSignal;
    OvenCyclePhaseInterface::CyclePhaseDescriptions m_phasesDescriptions;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context)
    {
        m_cyclePhase = cyclePhase;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const OvenCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context)
    {
        m_supportedCyclePhases = listOfCyclePhases;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnCyclePhasePropertyChanged(const qcc::String& objectPath, const uint8_t cyclePhase)
    {
        m_cyclePhaseSignal = cyclePhase;
        m_eventSignal.SetEvent();
    }

    virtual void OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const OvenCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases)
    {
        m_supportedCyclePhasesSignal = listOfCyclePhases;
        m_eventSignal.SetEvent();
    }

    virtual void OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions,
                                                      void* context, const char* errorName, const char* errorMessage)
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

        OvenCyclePhaseListener listener;
        CdmInterface* interface = m_controller->CreateInterface(OVEN_CYCLE_PHASE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        OvenCyclePhaseIntfController* controller = static_cast<OvenCyclePhaseIntfController*>(interface);
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
            status = controller->GetCyclePhasesDescriptions(invalidLang);
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
            status = controller->GetCyclePhasesDescriptions(validLang);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}