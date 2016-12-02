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

#ifndef CURRENTTEMPERATURECOMMANDS_H_
#define CURRENTTEMPERATURECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentTemperatureListener : public CurrentTemperatureIntfControllerListener {
  public:
    CurrentTemperatureListener();
    virtual ~CurrentTemperatureListener();

    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context);
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime);
};

class CurrentTemperatureCommands : public InterfaceCommands
{
  public:
    CurrentTemperatureCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentTemperatureCommands();

    virtual void Init();

    CurrentTemperatureIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentTemperatureIntfController* m_intfController;
    CurrentTemperatureListener m_listener;
};

#endif /* CURRENTTEMPERATURECOMMANDS_H_ */