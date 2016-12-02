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

#ifndef TARGETTEMPERATURELISTENER_H_
#define TARGETTEMPERATURELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TargetTemperatureListener : public TargetTemperatureIntfControlleeListener
{
  public:
    virtual QStatus OnSetTargetValue(const double value);
    virtual QStatus OnGetTargetValue(double& value);
    virtual QStatus OnGetMinValue(double& value);
    virtual QStatus OnGetMaxValue(double& value);
    virtual QStatus OnGetStepValue(double& value);
};

class TargetTemperatureCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TargetTemperatureCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TargetTemperatureCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TargetTemperatureIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdSetStepValue(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureIntfControllee* m_intfControllee;
    TargetTemperatureListener m_listener;
};



#endif /* TARGETTEMPERATURELISTENER_H_ */