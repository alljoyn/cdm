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

#ifndef OFFCONTROLCOMMANDS_H_
#define OFFCONTROLCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OffControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class OffControlListener : public OffControlIntfControllerListener {
  public:
    OffControlListener();
    virtual ~OffControlListener();
    virtual void OnSwitchOff(QStatus status, const qcc::String& objectPath, void* context,
                                         const char* errorName, const char* errorMessage);
};

class OffControlCommands : public InterfaceCommands
{
  public:
    OffControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~OffControlCommands();

    virtual void Init();

    OffControlIntfController* GetInterface() { return m_intfController; }

    static void OffCmdSwitchOff(Commands* commands, std::string& cmd);

  private:
    OffControlIntfController* m_intfController;
    OffControlListener m_listener;
};

#endif /* OFFCONTROLCOMMANDS_H_ */