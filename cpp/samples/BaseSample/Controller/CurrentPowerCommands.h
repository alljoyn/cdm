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

#ifndef CURRENTPOWERCOMMANDS_H_
#define CURRENTPOWERCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfController.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentPowerListener : public CurrentPowerIntfControllerListener {
  public:
    CurrentPowerListener();
    virtual ~CurrentPowerListener();
    virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double currentPower, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context);
    virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double currentPower);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime);

};

class CurrentPowerCommands : public InterfaceCommands
{
  public:
    CurrentPowerCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentPowerCommands();

    virtual void Init();

    CurrentPowerIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCurrentPower(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentPowerIntfController* m_intfController;
    CurrentPowerListener m_listener;
};

#endif /* CURRENTPOWERCOMMANDS_H_ */