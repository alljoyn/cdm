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

#ifndef ENERGYUSAGELISTENER_H_
#define ENERGYUSAGELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class EnergyUsageListener : public EnergyUsageIntfControlleeListener
{
  public:
    virtual QStatus OnGetCumulativeEnergy(double& cumulativeEnergy);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
    virtual QStatus OnResetCumulativeEnergy(ErrorCode& errorCode);
};

class EnergyUsageCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    EnergyUsageCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~EnergyUsageCommands();

    virtual void Init();

    EnergyUsageIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCumulativeEnergy(Commands* commands, std::string& cmd);
    static void OnCmdSetCumulativeEnergy(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdSetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    EnergyUsageIntfControllee* m_intfControllee;
    EnergyUsageListener m_listener;
};

#endif /* ENERGYUSAGELISTENER_H_ */