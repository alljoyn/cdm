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

#ifndef REMOTECONTROLLABILITYCOMMANDS_H_
#define REMOTECONTROLLABILITYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RemoteControllabilityListener : public RemoteControllabilityIntfControllerListener{
  public:
    RemoteControllabilityListener();
    virtual ~RemoteControllabilityListener();
    virtual void IsControllablePropertyChanged(const qcc::String& objectPath, const bool isControllable);
    virtual void GetIsControllablePropertyCallback(QStatus status, const qcc::String& objectPath, const bool isControllable, void* context);
};

class RemoteControllabilityCommands : public InterfaceCommands
{
  public:
    RemoteControllabilityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RemoteControllabilityCommands();

    virtual void Init();

    RemoteControllabilityIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetIsControllable(Commands* commands, std::string& cmd);
    //static void OnCmdSetIsClosed(Commands* commands, std::string& cmd);

  private:
    RemoteControllabilityIntfController* m_intfController;
    RemoteControllabilityListener m_listener;
};


#endif /* REMOTECONTROLLABILITYCOMMANDS_H_ */