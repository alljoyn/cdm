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

#ifndef SOILLEVELLISTENER_H_
#define SOILLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class SoilLevelListener : public SoilLevelIntfControlleeListener
{
  public:
    virtual QStatus OnGetMaxLevel(uint8_t& maxLevel);

    virtual QStatus OnSetMaxLevel(const uint8_t& maxLevel);

    virtual QStatus OnGetTargetLevel(uint8_t& targetLevel);

    virtual QStatus OnSetTargetLevel(const uint8_t& targetLevel);

    virtual QStatus OnGetSelectableLevels(std::vector<uint8_t>& selectableLevels);

    virtual QStatus OnSetSelectableLevels(const std::vector<uint8_t>& selectableLevels);
};

class SoilLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    SoilLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~SoilLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    SoilLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetSelectableLevels(Commands* commands, std::string& cmd);
//    static void OnCmdSetSupportedCyclePhases(Commands* commands, std::string& cmd);

  private:
    SoilLevelIntfControllee* m_intfControllee;
    SoilLevelListener m_listener;
};




#endif /* SOILLEVELLISTENER_H_ */