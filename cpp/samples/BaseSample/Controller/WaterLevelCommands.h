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

#ifndef WATERLEVELCOMMANDS_H_
#define WATERLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfController.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class WaterLevelListener : public WaterLevelIntfControllerListener{
  public:
    WaterLevelListener();
    virtual ~WaterLevelListener();
    virtual void OnGetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnGetSupplySourcePropertyCallback (QStatus status, const qcc::String& objectPath, const WaterLevelInterface::WaterLevelSupplySource value, void* context);
    virtual void OnGetCurrentLevelPropertyCallback (QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);

    virtual void MaxLevelProprtyChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void CurrentLevelProprtyChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void SupplySourceProprtyChanged(const qcc::String& objectPath, const WaterLevelInterface::WaterLevelSupplySource value);
};

class WaterLevelCommands : public InterfaceCommands
{
  public:
    WaterLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~WaterLevelCommands();

    virtual void Init();

    WaterLevelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetSupplySource(Commands* commands, std::string& cmd);

  private:
    WaterLevelIntfController* m_intfController;
    WaterLevelListener m_listener;
};


#endif /* WATERLEVELCOMMANDS_H_ */