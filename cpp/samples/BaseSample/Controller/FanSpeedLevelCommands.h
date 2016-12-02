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

#ifndef FANSPEEDLEVELCOMMANDS_H_
#define FANSPEEDLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class FanSpeedLevelListener : public FanSpeedLevelIntfControllerListener {
  public:
    FanSpeedLevelListener();
    virtual ~FanSpeedLevelListener();

    virtual void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t value);
};


class FanSpeedLevelCommands : public InterfaceCommands
{
  public:
    FanSpeedLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~FanSpeedLevelCommands();

    virtual void Init();

    FanSpeedLevelIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    FanSpeedLevelIntfController* m_intfController;
    FanSpeedLevelListener m_listener;
};

#endif /* FANSPEEDLEVELCOMMANDS_H_ */