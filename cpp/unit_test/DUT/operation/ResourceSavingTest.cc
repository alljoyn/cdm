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

#include <alljoyn/hae/interfaces/operation/ResourceSavingIntfController.h>
#include <alljoyn/hae/interfaces/operation/ResourceSavingIntfControllerListener.h>

class ResourceSavingListener : public ResourceSavingIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    bool m_resourceSavingMode;
    bool m_resourceSavingModeSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetResourceSavingMode(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_errorName = "";
        m_errorMessage = "";

        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetResourceSavingMode(QStatus status, const qcc::String& objectPath, const bool value, void* context)
    {
        m_errorName = "";
        m_errorMessage = "";

        m_resourceSavingMode = value;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResourceSavingModeChanged(const qcc::String& objectPath, const bool value)
    {
        m_resourceSavingModeSignal = value;
        m_eventSignal.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_ResourceSaving)
{
    WaitForControllee(RESOURCE_SAVING_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        ResourceSavingListener listener;
        HaeInterface* interface = m_controller->CreateInterface(RESOURCE_SAVING_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        ResourceSavingIntfController* controller = static_cast<ResourceSavingIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the ResourceSavingMode property.");
            status = controller->GetResourceSavingMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the ResourceSavingMode property to false.");
            if (listener.m_resourceSavingMode != false) {
                status = controller->SetResourceSavingMode(false);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_resourceSavingModeSignal, false);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("Set the ResourceSavingMode property to true.");
            status = controller->SetResourceSavingMode(true);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_3("Wait the PropertiesChanged signal for the ResourceSavingMode property.");
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT)) << "property changed signal is missing";
            listener.m_eventSignal.ResetEvent();
            EXPECT_EQ(listener.m_resourceSavingModeSignal, true);

            TEST_LOG_3("Get the ResourceSavingMode property.");
            status = controller->GetResourceSavingMode();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
            EXPECT_EQ(listener.m_resourceSavingMode, true);
        }
    }
}
