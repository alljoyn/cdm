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

#include <alljoyn/hae/interfaces/operation/LaundryCyclePhaseIntfController.h>
#include <alljoyn/hae/interfaces/operation/LaundryCyclePhaseIntfControllerListener.h>
using namespace std;
class LaundryCyclePhaseListener : public LaundryCyclePhaseIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_cyclePhase;
    LaundryCyclePhaseInterface::SupportedCyclePhases m_supportedCyclePhases;
    uint8_t m_cyclePhaseSignal;
    LaundryCyclePhaseInterface::SupportedCyclePhases m_supportedCyclePhasesSignal;
    LaundryCyclePhaseInterface::CyclePhaseDescriptions m_phasesDescriptions;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context)
    {
        m_cyclePhase = cyclePhase;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const LaundryCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context)
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

    virtual void OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const LaundryCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases)
    {
        m_supportedCyclePhasesSignal = listOfCyclePhases;
        m_eventSignal.SetEvent();
    }

    virtual void OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const LaundryCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions,
                                                      void* context, const char* errorName, const char* errorMessage)
    {
        m_phasesDescriptions = listOfCycleDescriptions;
        if(status != ER_OK)
        {
            m_errorMessage = errorMessage;
            m_errorName = errorName;
        }

        m_status = status;
        m_event.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_LaundryCyclePhaseTest)
{
    WaitForControllee(LAUNDRY_CYCLE_PHASE_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        LaundryCyclePhaseListener listener;
        HaeInterface* interface = m_controller->CreateInterface(LAUNDRY_CYCLE_PHASE_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        LaundryCyclePhaseIntfController* controller = static_cast<LaundryCyclePhaseIntfController*>(interface);
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
            EXPECT_STREQ(listener.m_errorName.c_str(), HaeInterface::GetInterfaceErrorName(LANGUAGE_NOT_SUPPORTED).c_str());
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
