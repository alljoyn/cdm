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

#ifndef TIMERCOMMANDS_H_
#define TIMERCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/TimerIntfController.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TimerListener : public TimerIntfControllerListener{
  public:
    TimerListener();
    virtual ~TimerListener();

    virtual void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, int32_t& time, void* context);
    virtual void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, int32_t& time, void* context);
    virtual void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, int32_t& time, void* context);
    virtual void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, int32_t& time, void* context);
    virtual void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, int32_t& time, void* context);
    virtual void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, int32_t& time, void* context);

    virtual void OnReferenceTimerPropertyChanged(const qcc::String& objectPath, int32_t time);
    virtual void OnTargetTimeToStartPropertyChanged(const qcc::String& objectPath, int32_t time);
    virtual void OnTargetTimeToStopPropertyChanged(const qcc::String& objectPath, int32_t time);
    virtual void OnEstimatedTimeToEndPropertyChanged(const qcc::String& objectPath, int32_t time);
    virtual void OnRunningTimePropertyChanged(const qcc::String& objectPath, int32_t time);
    virtual void OnTargetDurationPropertyChanged(const qcc::String& objectPath, int32_t time);

    virtual void OnResponseSetTargetTimerToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
    virtual void OnResponseSetTargetTimerToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
};

class TimerCommands : public InterfaceCommands
{
  public:
    TimerCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TimerCommands();

    virtual void Init();

    TimerIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetReferenceTimer(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetTimeToStart(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetTimeToStop(Commands* commands, std::string& cmd);
    static void OnCmdGetEstimatedTimeToEnd(Commands* commands, std::string& cmd);
    static void OnCmdGetRunningTime(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetDuration(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetTimeToStart(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetTimeToStop(Commands* commands, std::string& cmd);

  private:
    TimerIntfController* m_intfController;
    TimerListener m_listener;
};


#endif /* TIMERCOMMANDS_H_ */