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

#ifndef FANSPEEDLEVELLISTENER_H_
#define FANSPEEDLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class FanSpeedLevelListener : public FanSpeedLevelIntfControlleeListener
{
  public:
    virtual QStatus OnSetFanSpeedLevel(const uint8_t& value);
    virtual QStatus OnGetFanSpeedLevel(uint8_t& value);
    virtual QStatus OnGetMaxFanSpeedLevel(uint8_t& value);
    virtual QStatus OnSetAutoMode(const uint8_t& value);
    virtual QStatus OnGetAutoMode(uint8_t& value);
};

class FanSpeedLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    FanSpeedLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~FanSpeedLevelCommands();

    virtual void Init();

    FanSpeedLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    FanSpeedLevelIntfControllee* m_intfControllee;
    FanSpeedLevelListener m_listener;
};

#endif /* FANSPEEDLEVELLISTENER_H_ */