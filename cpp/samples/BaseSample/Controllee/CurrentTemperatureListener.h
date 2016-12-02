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

#ifndef CURRENTTEMPERATURELISTENER_H_
#define CURRENTTEMPERATURELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentTemperatureListener : public CurrentTemperatureIntfControlleeListener
{
  public:
    virtual QStatus OnGetCurrentValue(double& value);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
};

class CurrentTemperatureCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentTemperatureCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentTemperatureCommands();

    virtual void Init();

    CurrentTemperatureIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdSetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentTemperatureIntfControllee* m_intfControllee;
    CurrentTemperatureListener m_listener;
};

#endif /* CURRENTTEMPERATURELISTENER_H_ */