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

#ifndef CURRENTHUMIDITYCOMMANDS_H_
#define CURRENTHUMIDITYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentHumidityListener : public CurrentHumidityIntfControllerListener {
  public:
    CurrentHumidityListener();
    virtual ~CurrentHumidityListener();

    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value);
};

class CurrentHumidityCommands : public InterfaceCommands
{
  public:
    CurrentHumidityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentHumidityCommands();

    virtual void Init();

    CurrentHumidityIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);

  private:
    CurrentHumidityIntfController* m_intfController;
    CurrentHumidityListener m_listener;
};

#endif /* CURRENTHUMIDITYCOMMANDS_H_ */