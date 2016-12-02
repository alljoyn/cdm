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

#ifndef MOISTUREOUTPUTLEVELCOMMANDS_H_
#define MOISTUREOUTPUTLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class MoistureOutputLevelListener : public MoistureOutputLevelIntfControllerListener {
  public:
    MoistureOutputLevelListener();
    virtual ~MoistureOutputLevelListener();

    virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t autoMode);

    virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t autoMode, void* context);
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context);
};


class MoistureOutputLevelCommands : public InterfaceCommands
{
  public:
    MoistureOutputLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~MoistureOutputLevelCommands();

    virtual void Init();

    MoistureOutputLevelIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    MoistureOutputLevelIntfController* m_intfController;
    MoistureOutputLevelListener m_listener;
};

#endif /* MOISTUREOUTPUTLEVELCOMMANDS_H_ */