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

#ifndef CURRENTPOWERLISTENER_H_
#define CURRENTPOWERLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentPowerListener : public CurrentPowerIntfControlleeListener
{
  public:
    virtual QStatus OnSetCurrentPower(const double currentPower);
    virtual QStatus OnGetCurrentPower(double& currentPower);
    virtual QStatus OnSetPrecision(const double precision);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnSetUpdateMinTime(const uint16_t updateMinTime);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
};

class CurrentPowerCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentPowerCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentPowerCommands();

    virtual void Init();

    CurrentPowerIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentPower(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentPower(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdSetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentPowerIntfControllee* m_intfControllee;
    CurrentPowerListener m_listener;
};

#endif /* CURRENTPOWERLISTENER_H_ */