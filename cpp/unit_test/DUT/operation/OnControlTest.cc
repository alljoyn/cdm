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

#include <alljoyn/hae/interfaces/operation/OnControlIntfController.h>
#include <alljoyn/hae/interfaces/operation/OnControlIntfControllerListener.h>

class OnControlListener : public OnControlIntfControllerListener
{
public:
    qcc::Event m_event;
    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSwitchOn(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
    {
        if (status != ER_OK) {
            if (errorName) m_errorName = errorName;
            if (errorMessage) m_errorMessage = errorMessage;
        }
        m_status = status;
        m_event.SetEvent();
    }
};

TEST_F(HAETest, HAE_v1_19)
{
    WaitForControllee (ON_CONTROL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        OnControlListener listener;
        HaeInterface* interface = m_controller->CreateInterface(ON_CONTROL_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        OnControlIntfController* controller = static_cast<OnControlIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Call method.");
        {
            TEST_LOG_2("Call the SwitchOn method.");
            status = controller->SwitchOn();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}
