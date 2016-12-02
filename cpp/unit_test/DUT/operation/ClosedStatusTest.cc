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

#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllerListener.h>

class ClosedStatusListener : public ClosedStatusIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    bool m_isClosed;
    bool m_isClosedSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void GetIsClosedPropertyCallback(QStatus status, const qcc::String& objectPath, const bool isClosed, void* context)
    {
        m_status = status;
        m_isClosed = isClosed;
        m_event.SetEvent();
    }

    virtual void IsClosedPropertyChanged(const qcc::String& objectPath, const bool isClosed)
    {
        m_isClosedSignal = isClosed;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_ClosedStatus)
{
    WaitForControllee(CLOSED_STATUS_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        ClosedStatusListener listener;
        CdmInterface* interface = m_controller->CreateInterface(CLOSED_STATUS_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        ClosedStatusIntfController* controller = static_cast<ClosedStatusIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the IsClosed property.");
            status = controller->GetIsClosed();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}