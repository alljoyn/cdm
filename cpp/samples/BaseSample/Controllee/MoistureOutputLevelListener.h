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

#ifndef MOISTUREOUTPUTLEVELLISTENER_H_
#define MOISTUREOUTPUTLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class MoistureOutputLevelListener : public MoistureOutputLevelIntfControlleeListener
{
  public:
    virtual QStatus OnSetMoistureOutputLevel(const uint8_t& value);
    virtual QStatus OnGetMoistureOutputLevel(uint8_t& value);
    virtual QStatus OnGetMaxMoistureOutputLevel(uint8_t& value);
    virtual QStatus OnSetAutoMode(const uint8_t& autoMode);
    virtual QStatus OnGetAutoMode(uint8_t& autoMode);
};

class MoistureOutputLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    MoistureOutputLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~MoistureOutputLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    MoistureOutputLevelIntfControllee* GetInterface() { return m_intfControllee; }

    static void OnCmdGetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    MoistureOutputLevelIntfControllee* m_intfControllee;
    MoistureOutputLevelListener m_listener;
};

#endif /* MOISTUREOUTPUTLEVELLISTENER_H_ */