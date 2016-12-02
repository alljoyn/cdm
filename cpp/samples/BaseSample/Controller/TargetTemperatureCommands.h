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

#ifndef TARGETTEMPERATURECOMMANDS_H_
#define TARGETTEMPERATURECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TargetTemperatureListener : public TargetTemperatureIntfControllerListener {
  public:
    TargetTemperatureListener();
    virtual ~TargetTemperatureListener();

    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context);

    virtual void OnTargetValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const  double value);
    virtual void OnStepValueChanged(const qcc::String& objectPath, const double value);

};

class TargetTemperatureCommands : public InterfaceCommands
{
  public:
    TargetTemperatureCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TargetTemperatureCommands();

    virtual void Init();

    TargetTemperatureIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);

    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureIntfController* m_intfController;
    TargetTemperatureListener m_listener;
};

#endif /* TARGETTEMPERATURECOMMANDS_H_ */