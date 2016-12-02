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

#ifndef SPINSPEEDLEVELCOMMANDS_H_
#define SPINSPEEDLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class SpinSpeedLevelListener : public SpinSpeedLevelIntfControllerListener{
  public:
    SpinSpeedLevelListener();
    virtual ~SpinSpeedLevelListener();
    virtual void GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context);

    virtual void GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context);

    virtual void SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

    virtual void GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context);

    virtual void MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel);

    virtual void TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel);

    virtual void SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels);

};

class SpinSpeedLevelCommands : public InterfaceCommands
{
  public:
    SpinSpeedLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~SpinSpeedLevelCommands();

    virtual void Init();

    SpinSpeedLevelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableLevels(Commands* commands, std::string& cmd);

  private:
    SpinSpeedLevelIntfController* m_intfController;
    SpinSpeedLevelListener m_listener;
};


#endif /* SPINSPEEDLEVELCOMMANDS_H_ */