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

#ifndef SPINSPEEDLEVELLISTENER_H_
#define SPINSPEEDLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class SpinSpeedLevelListener : public SpinSpeedLevelIntfControlleeListener
{
  public:
    virtual QStatus OnGetMaxLevel(uint8_t& maxLevel);

    virtual QStatus OnSetMaxLevel(const uint8_t& maxLevel);

    virtual QStatus OnGetTargetLevel(uint8_t& targetLevel);

    virtual QStatus OnSetTargetLevel(const uint8_t& targetLevel);

    virtual QStatus OnGetSelectableLevels(std::vector<uint8_t>& selectableLevels);

    virtual QStatus OnSetSelectableLevels(const std::vector<uint8_t>& selectableLevels);
};

class SpinSpeedLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    SpinSpeedLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~SpinSpeedLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    SpinSpeedLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetSelectableLevels(Commands* commands, std::string& cmd);
//    static void OnCmdSetSupportedCyclePhases(Commands* commands, std::string& cmd);

  private:
    SpinSpeedLevelIntfControllee* m_intfControllee;
    SpinSpeedLevelListener m_listener;
};


#endif /* SPINSPEEDLEVELLISTENER_H_ */