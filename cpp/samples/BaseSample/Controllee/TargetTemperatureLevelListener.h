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

#ifndef TARGETTEMPERATURELEVELLISTENER_H_
#define TARGETTEMPERATURELEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TargetTemperatureLevelListener : public TargetTemperatureLevelIntfControlleeListener
{
  public:
    virtual QStatus OnSetTargetLevel(const uint8_t value);
    virtual QStatus OnGetTargetLevel(uint8_t& value);
    virtual QStatus OnGetMaxLevel(uint8_t& value);
    virtual QStatus OnGetSelectableTemperatureLevels(TargetTemperatureLevelInterface::TemperatureLevels& value);
};

class TargetTemperatureLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TargetTemperatureLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TargetTemperatureLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TargetTemperatureLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableTemperatureLevels(Commands* commands, std::string& cmd);
    static void OnCmdSetSelectableTemperatureLevels(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureLevelIntfControllee* m_intfControllee;
    TargetTemperatureLevelListener m_listener;
};

#endif /* TARGETTEMPERATURELEVELLISTENER_H_ */