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

#ifndef SOILLEVELCOMMANDS_H_
#define SOILLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class SoilLevelListener : public SoilLevelIntfControllerListener {
  public:
    SoilLevelListener();
    virtual ~SoilLevelListener();
    virtual void GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context);

    virtual void GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context);

    virtual void SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

    virtual void GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context);

    virtual void MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel);

    virtual void TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel);

    virtual void SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels);

};

class SoilLevelCommands : public InterfaceCommands
{
  public:
    SoilLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~SoilLevelCommands();

    virtual void Init();

    SoilLevelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableLevels(Commands* commands, std::string& cmd);

  private:
    SoilLevelIntfController* m_intfController;
    SoilLevelListener m_listener;
};


#endif /* SOILLEVELCOMMANDS_H_ */