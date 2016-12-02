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

#ifndef WATERLEVELLISTENER_H_
#define WATERLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class WaterLevelListener : public WaterLevelIntfControlleeListener
{
  public:
        virtual QStatus OnGetCurrentLevel(uint8_t& currentLevel);

        virtual QStatus OnGetMaxLevel(uint8_t& maxLevel);

        virtual QStatus OnGetSupplySource(WaterLevelInterface::WaterLevelSupplySource& supplySource);
};

class WaterLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    WaterLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~WaterLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    WaterLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetSupplySource(Commands* commands, std::string& cmd);
    static void OnCmdSetSupplySource(Commands* commands, std::string& cmd);

  private:
    WaterLevelIntfControllee* m_intfControllee;
    WaterLevelListener m_listener;
};

#endif /* WATERLEVELLISTENER_H_ */