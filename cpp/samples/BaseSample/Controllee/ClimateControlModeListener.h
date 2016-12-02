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

#ifndef CLIMATECONTROLMODELISTENER_H_
#define CLIMATECONTROLMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class ClimateControlModeListener : public ClimateControlModeIntfControlleeListener
{
  public:
    virtual QStatus OnSetMode(const uint16_t& mode);
    virtual QStatus OnGetMode(uint16_t& mode);
    virtual QStatus OnGetSupportedModes(SupportedModes& modes);
    virtual QStatus OnGetOperationalState(uint16_t& operationalState);
};

class ClimateControlModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    ClimateControlModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~ClimateControlModeCommands();

    virtual void Init();
    virtual void InitializeProperties();

    ClimateControlModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);
    static void OnCmdGetOperationalState(Commands* commands, std::string& cmd);
    static void OnCmdSetOperationalState(Commands* commands, std::string& cmd);

  private:
    ClimateControlModeIntfControllee* m_intfControllee;
    ClimateControlModeListener m_listener;
};

#endif /* CLIMATECONTROLMODELISTENER_H_ */