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

#ifndef ONCONTROLCOMMANDS_H_
#define ONCONTROLCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OnControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class OnControlListener : public OnControlIntfControllerListener {
  public:
    OnControlListener();
    virtual ~OnControlListener();
    virtual void OnResponseSwitchOn(QStatus status, const qcc::String& objectPath, void* context,
                                    const char* errorName, const char* errorMessage);
};

class OnControlCommands : public InterfaceCommands
{
  public:
    OnControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~OnControlCommands();

    virtual void Init();

    OnControlIntfController* GetInterface() { return m_intfController; }

    static void OnCmdSwitchOn(Commands* commands, std::string& cmd);

  private:
    OnControlIntfController* m_intfController;
    OnControlListener m_listener;
};

#endif /* ONCONTROLCOMMANDS_H_ */