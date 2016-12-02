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

#ifndef CURRENTAIRQUALITYLISTENER_H_
#define CURRENTAIRQUALITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentAirQualityListener : public CurrentAirQualityIntfControlleeListener
{
  public:
    virtual QStatus OnGetContaminantType(uint8_t& type);
    virtual QStatus OnGetCurrentValue(double& value);
    virtual QStatus OnGetMaxValue(double& value);
    virtual QStatus OnGetMinValue(double& value);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
};

class CurrentAirQualityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentAirQualityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentAirQualityCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CurrentAirQualityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdSetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdSetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityIntfControllee* m_intfControllee;
    CurrentAirQualityListener m_listener;
};



#endif /* CURRENTAIRQUALITYLISTENER_H_ */