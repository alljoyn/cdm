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

#ifndef HVACFANMODELISTENER_H_
#define HVACFANMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class HvacFanModeListener : public HvacFanModeIntfControlleeListener
{
  public:
    virtual QStatus OnSetMode(const uint16_t& mode);
    virtual QStatus OnGetMode(uint16_t& mode);
    virtual QStatus OnGetSupportedModes(SupportedModes& modes);
};

class HvacFanModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    HvacFanModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~HvacFanModeCommands();

    virtual void Init();
    virtual void InitializeProperties();

    HvacFanModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);

  private:
    HvacFanModeIntfControllee* m_intfControllee;
    HvacFanModeListener m_listener;
};

#endif /* HVACFANMODELISTENER_H_ */