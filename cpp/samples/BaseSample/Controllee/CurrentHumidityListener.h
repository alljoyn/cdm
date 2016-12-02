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

#ifndef CURRENTHUMIDITYLISTENER_H_
#define CURRENTHUMIDITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentHumidityListener : public CurrentHumidityIntfControlleeListener
{
  public:
    virtual QStatus OnGetCurrentValue(uint8_t& value);
    virtual QStatus OnGetMaxValue(uint8_t& value);
};

class CurrentHumidityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentHumidityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentHumidityCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CurrentHumidityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);

  private:
    CurrentHumidityIntfControllee* m_intfControllee;
    CurrentHumidityListener m_listener;
};

#endif /* CURRENTHUMIDITYLISTENER_H_ */