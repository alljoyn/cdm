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

#ifndef CURRENTAIRQUALITYLEVELLISTENER_H_
#define CURRENTAIRQUALITYLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentAirQualityLevelListener : public CurrentAirQualityLevelIntfControlleeListener
{
  public:
    virtual QStatus OnGetContaminantType(uint8_t& type);
    virtual QStatus OnGetCurrentLevel(uint8_t& value);
    virtual QStatus OnGetMaxLevel(uint8_t& value);
};

class CurrentAirQualityLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentAirQualityLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentAirQualityLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CurrentAirQualityLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdSetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityLevelIntfControllee* m_intfControllee;
    CurrentAirQualityLevelListener m_listener;
};



#endif /* CURRENTAIRQUALITYLEVELLISTENER_H_ */