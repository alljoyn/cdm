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

#ifndef REMOTECONTROLLABILITYLISTENER_H_
#define REMOTECONTROLLABILITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class RemoteControllabilityListener : public RemoteControllabilityIntfControlleeListener
{
  public:
    virtual QStatus OnGetIsControllable(bool& isControllable);
};


class RemoteControllabilityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RemoteControllabilityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RemoteControllabilityCommands();

    virtual void Init();

    RemoteControllabilityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetIsControllable(Commands* commands, std::string& cmd);
    static void OnCmdSetIsControllable(Commands* commands, std::string& cmd);

  private:
    RemoteControllabilityIntfControllee* m_intfControllee;
    RemoteControllabilityListener m_listener;
};


#endif /* REMOTECONTROLLABILITYLISTENER_H_ */