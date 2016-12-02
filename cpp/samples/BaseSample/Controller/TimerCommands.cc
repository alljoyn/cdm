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

#include "TimerCommands.h"
#include "ControllerSample.h"

TimerListener::TimerListener()
{
}

TimerListener::~TimerListener()
{
}
void TimerListener::OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, const int32_t time, void* context)
{
    cout << "# TimerListener::OnResponseGetReferenceTimer" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, const int32_t time, void* context)
{
    cout << "# TimerListener::OnResponseGetTargetTimeToStart" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, const int32_t time, void* context)
{
    cout << "# TimerListener::OnResponseGetTargetTimeToStop" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, const int32_t time, void* context)
{
    cout << "# TimerListener::OnResponseGetEstimatedTimeToEnd" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, const int32_t time, void* context)
{
    cout << "# TimerListener::OnResponseGetRunningTime" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, const int32_t time, void* context)
{
    cout << "# TimerListener::OnResponseGetTargetDuration" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnReferenceTimerChanged(const qcc::String& objectPath, int32_t time)
{
    cout << "# TimerListener::OnReferenceTimerChanged" << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnTargetTimeToStartChanged(const qcc::String& objectPath, int32_t time)
{
    cout << "# TimerListener::OnTargetTimeToStartChanged" << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnTargetTimeToStopChanged(const qcc::String& objectPath, int32_t time)
{
    cout << "# TimerListener::OnTargetTimeToStopChanged" << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnEstimatedTimeToEndChanged(const qcc::String& objectPath, int32_t time)
{
    cout << "# TimerListener::OnEstimatedTimeToEndChanged" << endl;
    cout << "# time: " << (int)time << endl;
}
void TimerListener::OnRunningTimeChanged(const qcc::String& objectPath, int32_t time)
{
    cout << "TimerListener::OnRunningTimeChanged" << endl;
    cout << "time: " << (int)time << endl;
}
void TimerListener::OnTargetDurationChanged(const qcc::String& objectPath, int32_t time)
{
    cout << "# TimerListener::OnTargetDurationChanged" << endl;
    cout << "# time: " << (int)time << endl;
}

void TimerListener::OnResponseSetTargetTimeToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    cout << "# TimerListener::OnResponseSetTargetTimeToStart" << endl;
    cout << "# Status: " << QCC_StatusText(status) << endl;
    if(status != ER_OK)
    {
        cout << "# error name: " << errorName << endl;
        cout << "# error mess: " << errorMessage << endl;
    }
}
void TimerListener::OnResponseSetTargetTimeToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    cout << "# TimerListener::OnResponseSetTargetTimeToStop" << endl;
    cout << "# Status: " << QCC_StatusText(status) << endl;
    if(status != ER_OK)
    {
        cout << "error name: " << errorName << endl;
        cout << "error mess: " << errorMessage << endl;
    }
}





TimerCommands::TimerCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

TimerCommands::~TimerCommands()
{

}

void TimerCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TIMER_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<TimerIntfController*>(cdmInterface);
    }

    RegisterCommand(&TimerCommands::OnCmdGetReferenceTimer, "grt", "get reference timer");
    RegisterCommand(&TimerCommands::OnCmdGetTargetTimeToStart, "gttsa", "get target time to start");
    RegisterCommand(&TimerCommands::OnCmdGetTargetTimeToStop, "gttsp", "get target time to stop");
    RegisterCommand(&TimerCommands::OnCmdGetEstimatedTimeToEnd, "gette", "get estimated time to end");
    RegisterCommand(&TimerCommands::OnCmdGetRunningTime, "grunt", "get running time");
    RegisterCommand(&TimerCommands::OnCmdGetTargetDuration, "gtd", "get target duration");
    RegisterCommand(&TimerCommands::OnCmdSetTargetTimeToStart, "ststart", "Set target time to start");
    RegisterCommand(&TimerCommands::OnCmdSetTargetTimeToStop, "ststop", "set target time to stop");
    PrintCommands();
}

void TimerCommands::OnCmdGetReferenceTimer(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetReferenceTimer();
}
void TimerCommands::OnCmdGetTargetTimeToStart(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetTimeToStart();
}
void TimerCommands::OnCmdGetTargetTimeToStop(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetTimeToStop();
}
void TimerCommands::OnCmdGetEstimatedTimeToEnd(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetEstimatedTimeToEnd();
}
void TimerCommands::OnCmdGetRunningTime(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetRunningTime();
}
void TimerCommands::OnCmdGetTargetDuration(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetDuration();
}

void TimerCommands::OnCmdSetTargetTimeToStart(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    int time = strtol(cmd.c_str(), NULL, 10);
    intfController->SetTargetTimeToStart(time);
}

void TimerCommands::OnCmdSetTargetTimeToStop(Commands* commands, std::string& cmd)
{
    TimerIntfController* intfController = static_cast<TimerCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    int time = strtol(cmd.c_str(), NULL, 10);
    intfController->SetTargetTimeToStop(time);
}
