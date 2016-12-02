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

#ifndef TARGETHUMIDITYLISTENER_H_
#define TARGETHUMIDITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TargetHumidityListener : public TargetHumidityIntfControlleeListener
{
  public:
    virtual QStatus OnSetTargetValue(const uint8_t value);
    virtual QStatus OnGetTargetValue(uint8_t& value);
    virtual QStatus OnGetMinValue(uint8_t& value);
    virtual QStatus OnGetMaxValue(uint8_t& value);
    virtual QStatus OnGetStepValue(uint8_t& value);
    virtual QStatus OnGetSelectableHumidityLevels(TargetHumidityInterface::HumidityLevels& value);
};

class TargetHumidityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TargetHumidityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TargetHumidityCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TargetHumidityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdSetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableHumidityLevels(Commands* commands, std::string& cmd);
    static void OnCmdSetSelectableHumidityLevels(Commands* commands, std::string& cmd);

  private:
    TargetHumidityIntfControllee* m_intfControllee;
    TargetHumidityListener m_listener;
};



#endif /* TARGETHUMIDITYLISTENER_H_ */