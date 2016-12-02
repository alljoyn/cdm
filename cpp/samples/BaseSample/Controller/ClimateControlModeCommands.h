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

#ifndef CLIMATECONTROLMODECOMMANDS_H_
#define CLIMATECONTROLMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class ClimateControlModeListener : public ClimateControlModeIntfControllerListener {
  public:
    ClimateControlModeListener();
    virtual ~ClimateControlModeListener();

    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context);
    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnModeChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value);
    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const uint16_t value);
};


class ClimateControlModeCommands : public InterfaceCommands
{
  public:
    ClimateControlModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~ClimateControlModeCommands();

    virtual void Init();

    ClimateControlModeIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);
    static void OnCmdGetOperationalState(Commands* commands, std::string& cmd);

  private:
    ClimateControlModeIntfController* m_intfController;
    ClimateControlModeListener m_listener;
};

#endif /* CLIMATECONTROLMODECOMMANDS_H_ */