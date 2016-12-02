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

#ifndef HVACFANMODECOMMANDS_H_
#define HVACFANMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class HvacFanModeListener : public HvacFanModeIntfControllerListener {
  public:
    HvacFanModeListener();
    virtual ~HvacFanModeListener();

    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context);
    virtual void OnModeChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value);
};


class HvacFanModeCommands : public InterfaceCommands
{
  public:
    HvacFanModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~HvacFanModeCommands();

    virtual void Init();

    HvacFanModeIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);

  private:
    HvacFanModeIntfController* m_intfController;
    HvacFanModeListener m_listener;
};

#endif /* HVACFANMODECOMMANDS_H_ */