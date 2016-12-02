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

#ifndef BATTERYSTATUSLISTENER_H_
#define BATTERYSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class BatteryStatusListener : public BatteryStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetCurrentValue(uint8_t& currentValue);
    virtual QStatus OnGetIsCharging(bool& isCharging);

};

class BatteryStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    BatteryStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~BatteryStatusCommands();

    virtual void Init();

    BatteryStatusIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetIsCharging(Commands* commands, std::string& cmd);
    static void OnCmdSetIsCharging(Commands* commands, std::string& cmd);

  private:
    BatteryStatusIntfControllee* m_intfControllee;
    BatteryStatusListener m_listener;
};

#endif /* BATTERYSTATUSLISTENER_H_ */