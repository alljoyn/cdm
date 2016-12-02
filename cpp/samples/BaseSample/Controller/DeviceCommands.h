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

#ifndef DEVICECOMMANDS_H_
#define DEVICECOMMANDS_H_

#include "ControllerCommands.h"
#include <alljoyn/cdm/DeviceInfo.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class DeviceCommands : public ControllerCommands
{
  public:
    DeviceCommands(ControllerSample* sample, DeviceInfoPtr& info);
    virtual ~DeviceCommands();

    virtual void Init();

    ControllerSample* GetControllerSample() { return m_sample; }
    DeviceInfoPtr& GetDeviceInfo() { return m_deviceInfo; }
    static void OnCmdSelectInterface(Commands* commands, std::string&);
    static void OnCmdBack(Commands* commands, std::string& cmd);

  private:
    ControllerSample* m_sample;
    DeviceInfoPtr m_deviceInfo;

    static Commands* CreateInterfaceCommands(Commands* commands, const char* intfName, const char* objectPath);
};


#endif