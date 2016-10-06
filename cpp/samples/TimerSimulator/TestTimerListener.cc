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

#include <iostream>

#include "TestTimerListener.h"
#include "TestControllee.h"

using namespace std;

TestTimerListener::TestTimerListener(void* controllee)
{
    m_testControllee = controllee;
}
QStatus TestTimerListener::GetReferenceTimer(int32_t& time)
{
    cout << "TestTimerListener::GetReferenceTimer" <<endl;
    return ER_OK;
}

QStatus TestTimerListener::GetTargetTimeToStart(int32_t& time)
{
    cout << "TestTimerListener::GetTargetTimeToStart" <<endl;
    return ER_OK;
}

QStatus TestTimerListener::GetTargetTimeToStop(int32_t& time)
{
    cout << "TestTimerListener::GetTargetTimeToStop" <<endl;
    return ER_OK;
}

QStatus TestTimerListener::GetEstimatedTimeToEnd(int32_t& time)
{
    cout << "TestTimerListener::GetEstimatedTimeToEnd" <<endl;
    return ER_OK;
}

QStatus TestTimerListener::GetRunningTime(int32_t& time)
{
    cout << "TestTimerListener::GetRunningTime" <<endl;
    return ER_OK;
}

QStatus TestTimerListener::GetTargetDuration(int32_t& time)
{
    cout << "TestTimerListener::GetTargetDuration" <<endl;
    return ER_OK;
}

QStatus TestTimerListener::OnSetTargetTimeToStart(int32_t time, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "TestTimerListener::OnSetTargetTimeToStart" <<endl;
    cout << "time: " << (int)time << endl;
    TestControllee *controllee =  static_cast<TestControllee*>(m_testControllee);
    if(time < controllee->TimerIntf()->GetReferenceTimer())
    {
        errorCode = ErrorCode::INVALID_VALUE;
        status = ER_FAIL;
    }
    else
    {
        status = controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START);
    }
    return status;
}

QStatus TestTimerListener::OnSetTargetTimeToStop(int32_t time, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "TestTimerListener::OnSetTargetTimeToStop" <<endl;
    cout << "time: " << (int)time << endl;
    TestControllee *controllee =  static_cast<TestControllee*>(m_testControllee);
    if(time < controllee->TimerIntf()->GetReferenceTimer() || time < controllee->TimerIntf()->GetTargetTimeToStart())
    {
        errorCode = ErrorCode::INVALID_VALUE;
        status = ER_FAIL;
    }
    return status;
}