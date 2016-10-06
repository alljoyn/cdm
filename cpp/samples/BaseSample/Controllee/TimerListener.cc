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

#include <iostream>
#include "TimerListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus TimerListener::GetReferenceTimer(int32_t& time)
{
    return ER_OK;
}

QStatus TimerListener::GetTargetTimeToStart(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetTargetTimeToStop(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetEstimatedTimeToEnd(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetRunningTime(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetTargetDuration(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::OnSetTargetTimeToStart(int32_t time, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "TimerListener::OnSetTargetTimeToStart" <<endl;
    if(time == TimerInterface::TIMER_FEATURE_NOT_APPLIED ||
       time == TimerInterface::TIMER_NOT_SUPPORTED )
    {
        errorCode = ErrorCode::INVALID_VALUE;
        status = ER_FAIL;
    }
    cout << "time: " << (int)time << endl;
    return status;
}

QStatus TimerListener::OnSetTargetTimeToStop(int32_t time, ErrorCode& errorCode)
{
    QStatus status = ER_OK;
    cout << "TimerListener::OnSetTargetTimeToStop" <<endl;
    if(time == TimerInterface::TIMER_FEATURE_NOT_APPLIED ||
       time == TimerInterface::TIMER_NOT_SUPPORTED )
    {
        errorCode = ErrorCode::INVALID_VALUE;
        status = ER_FAIL;
    }
    cout << "time: " << (int)time << endl;
    return status;
}


ControlleeCommands* TimerCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new TimerCommands(sample, objectPath);
}

TimerCommands::TimerCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

TimerCommands::~TimerCommands()
{
}

void TimerCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TIMER_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<TimerIntfControllee*>(cdmInterface);

        RegisterCommand(&TimerCommands::OnCmdGetReferenceTimer, "grt", "get reference timer");
        RegisterCommand(&TimerCommands::OnCmdSetReferenceTimer, "srt", "set reference timer");

        RegisterCommand(&TimerCommands::OnCmdGetTargetTimeToStart, "gtstart", "get target time to start");
        RegisterCommand(&TimerCommands::OnCmdSetTargetTimeToStart, "ststart", "set target time to start");

        RegisterCommand(&TimerCommands::OnCmdGetTargetTimeToStop, "gtstop", "get target time to stop");
        RegisterCommand(&TimerCommands::OnCmdSetTargetTimeToStop, "ststop", "set target time to stop");

        RegisterCommand(&TimerCommands::OnCmdGetEstimatedTimeToEnd, "gette", "get estimated time to end");

        RegisterCommand(&TimerCommands::OnCmdGetRunningTime, "grunt", "get running time");

        RegisterCommand(&TimerCommands::OnCmdGetTargetDuration, "gtd", "get target duration");
    } else {
        PrintCommands();
    }
}

void TimerCommands::InitializeProperties()
{
    if (m_intfControllee) {

    }
}

void TimerCommands::OnCmdGetReferenceTimer(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetReferenceTimer() << endl;
}
void TimerCommands::OnCmdSetReferenceTimer(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint32_t time = strtod(cmd.c_str(), NULL);
    intfControllee->SetReferenceTimer(time);
}

void TimerCommands::OnCmdGetTargetTimeToStart(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetTargetTimeToStart() << endl;
}
void TimerCommands::OnCmdSetTargetTimeToStart(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint32_t time = strtod(cmd.c_str(), NULL);
    intfControllee->SetTargetTimeToStart(time);
}

void TimerCommands::OnCmdGetTargetTimeToStop(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetTargetTimeToStop() << endl;
}
void TimerCommands::OnCmdSetTargetTimeToStop(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint32_t time = strtod(cmd.c_str(), NULL);
    intfControllee->SetTargetTimeToStop(time);
}

void TimerCommands::OnCmdGetEstimatedTimeToEnd(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetEstimatedTimeToEnd() << endl;
}

void TimerCommands::OnCmdGetRunningTime(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetRunningTime() << endl;
}

void TimerCommands::OnCmdGetTargetDuration(Commands* commands, std::string& cmd)
{
    TimerIntfControllee* intfControllee = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetTargetDuration() << endl;
}