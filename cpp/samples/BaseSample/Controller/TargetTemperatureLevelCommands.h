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

#ifndef TARGETTEMPERATURELEVELCOMMANDS_H_
#define TARGETTEMPERATURELEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TargetTemperatureLevelListener : public TargetTemperatureLevelIntfControllerListener {
  public:
    TargetTemperatureLevelListener();
    virtual ~TargetTemperatureLevelListener();

    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value, void* context);

    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const  uint8_t value);
    virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value);
};

class TargetTemperatureLevelCommands : public InterfaceCommands
{
  public:
    TargetTemperatureLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TargetTemperatureLevelCommands();

    virtual void Init();

    TargetTemperatureLevelIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableTemperatureLevels(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureLevelIntfController* m_intfController;
    TargetTemperatureLevelListener m_listener;
};

#endif /* TARGETTEMPERATURELEVELCOMMANDS_H_ */