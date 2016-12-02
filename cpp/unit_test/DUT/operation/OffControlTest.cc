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

#include <alljoyn/cdm/interfaces/operation/OffControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllerListener.h>

class OffControlListener : public OffControlIntfControllerListener
{
public:
    qcc::Event m_event;
    QStatus m_status;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSwitchOff(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
    {
        if (status != ER_OK) {
            if (errorName) {
                m_errorName = errorName;
            }
            if (errorMessage) {
                m_errorMessage = errorMessage;
            }
        }
         m_status = status;
        m_event.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_OffControl)
{
    WaitForControllee (OFF_CONTROL_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);
        OffControlListener listener;
        CdmInterface* interface = m_controller->CreateInterface(OFF_CONTROL_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        OffControlIntfController* controller = static_cast<OffControlIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Call method");
        {
            TEST_LOG_2("Call the SwitchOff method");
            {
                status = controller->SwitchOff();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
            }
        }
    }
}