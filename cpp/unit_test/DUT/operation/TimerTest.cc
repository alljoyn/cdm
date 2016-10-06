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
#include <algorithm>

#include <alljoyn/cdm/interfaces/operation/TimerIntfController.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllerListener.h>

class TimerListener : public TimerIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;

    uint32_t m_referenceTimer;
    uint32_t m_referenceTimerSignal;

    uint32_t m_targetTimeToStart;
    uint32_t m_targetTimeToStartSignal;

    uint32_t m_targetTimeToStop;
    uint32_t m_targetTimeToStopSignal;

    uint32_t m_estimatedTimeToEnd;
    uint32_t m_estimatedTimeToEndSignal;

    uint32_t m_runningTime;
    uint32_t m_runningTimeSignal;

    uint32_t m_targetDuration;
    uint32_t m_targetDurationSignal;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, int32_t& time, void* context)
    {
        m_status = status;
        m_referenceTimer = time;
        m_event.SetEvent();
    }
    virtual void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, int32_t& time, void* context)
    {
        m_status = status;
        m_targetTimeToStart = time;
        m_event.SetEvent();
    }
    virtual void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, int32_t& time, void* context)
    {
        m_status = status;
        m_targetTimeToStop = time;
        m_event.SetEvent();
    }
    virtual void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, int32_t& time, void* context)
    {
        m_status = status;
        m_estimatedTimeToEnd = time;
        m_event.SetEvent();
    }
    virtual void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, int32_t& time, void* context)
    {
        m_status = status;
        m_runningTime = time;
        m_event.SetEvent();
    }
    virtual void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, int32_t& time, void* context)
    {
        m_status = status;
        m_targetDuration = time;
        m_event.SetEvent();
    }
    virtual void OnReferenceTimerPropertyChanged(const qcc::String& objectPath, int32_t time)
    {
        m_referenceTimerSignal = time;
        m_eventSignal.SetEvent();
    }
    virtual void OnTargetTimeToStartPropertyChanged(const qcc::String& objectPath, int32_t time)
    {
        m_targetTimeToStartSignal = time;
        m_eventSignal.SetEvent();
    }
    virtual void OnTargetTimeToStopPropertyChanged(const qcc::String& objectPath, int32_t time)
    {
        m_targetTimeToStopSignal = time;
        m_eventSignal.SetEvent();
    }
    virtual void OnEstimatedTimeToEndPropertyChanged(const qcc::String& objectPath, int32_t time)
    {
        m_estimatedTimeToEndSignal = time;
        m_eventSignal.SetEvent();
    }
    virtual void OnRunningTimePropertyChanged(const qcc::String& objectPath, int32_t time)
    {
        m_runningTimeSignal = time;
        m_eventSignal.SetEvent();
    }
    virtual void OnTargetDurationPropertyChanged(const qcc::String& objectPath, int32_t time)
    {
        m_targetDurationSignal = time;
        m_eventSignal.SetEvent();
    }
    virtual void OnResponseSetTargetTimerToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
    {
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
    virtual void OnResponseSetTargetTimerToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
    {
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

TEST_F(CDMTest, CDM_v1_Timer)
{
    WaitForControllee(TIMER_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        TimerListener listener;
        CdmInterface* interface = m_controller->CreateInterface(TIMER_INTERFACE, m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        TimerIntfController* controller = static_cast<TimerIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the ReferenceTimer property.");
            status = controller->GetReferenceTimer();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve the TargetTimeToStart property.");
            status = controller->GetTargetTimeToStart();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve TargetTimeToStop property.");
            status = controller->GetTargetTimeToStop();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve EstimatedTimeToEnd property.");
            status = controller->GetEstimatedTimeToEnd();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve RunningTime property.");
            status = controller->GetRunningTime();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retrieve TargetDuration property.");
            status = controller->GetTargetDuration();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        TEST_LOG_1("Call methods with invalid params.");
        {
            TEST_LOG_2("Call SetTargetTimerToStart method with 0x80000000.");
            status = controller->SetTargetTimeToStart(TimerInterface::TIMER_FEATURE_NOT_APPLIED);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);
            EXPECT_STREQ(listener.m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());

            TEST_LOG_2("Call SetTargetTimerToStart method with 0x80000001.");
            status = controller->SetTargetTimeToStart(TimerInterface::TIMER_NOT_SUPPORTED);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);
            EXPECT_STREQ(listener.m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());

            TEST_LOG_2("Call SetTargetTimerToStop method with 0x80000000.");
            status = controller->SetTargetTimeToStop(TimerInterface::TIMER_FEATURE_NOT_APPLIED);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);
            EXPECT_STREQ(listener.m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());

            TEST_LOG_2("Call SetTargetTimerToStop method with 0x80000001.");
            status = controller->SetTargetTimeToStop(TimerInterface::TIMER_NOT_SUPPORTED);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_NE(listener.m_status, ER_OK);
            EXPECT_STREQ(listener.m_errorName.c_str(), CdmInterface::GetInterfaceErrorName(INVALID_VALUE).c_str());
        }

        TEST_LOG_1("Call methods with valid params.");
        {
            TEST_LOG_2("Call SetTargetTimerToStart method with 100.");
            const int32_t validTimeToStart = 100;
            status = controller->SetTargetTimeToStart(validTimeToStart);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Call SetTargetTimerToStop method with 200.");
            const int32_t validTimeToStop = 200;
            status = controller->SetTargetTimeToStop(validTimeToStop);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }
    }
}