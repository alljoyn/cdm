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

#ifndef CYCLECONTROLLISTENER_H_
#define CYCLECONTROLLISTENER_H_
#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControlleeListener.h>

using namespace ajn;
using namespace services;


class CycleControlListener : public CycleControlIntfControlleeListener
{
public:
    virtual QStatus OnGetOperationalState(CycleControlInterface::CycleControlOperationalState& state);

    virtual QStatus OnExecuteCommand(CycleControlInterface::CycleControlOperationalCommand command, CycleControlInterface::CycleControlOperationalState& newState, ErrorCode& error);

};

class CycleControlCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CycleControlCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CycleControlCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CycleControlIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetOperationalState(Commands* commands, std::string& cmd);
    static void OnCmdSetOperationalState(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedOperationalCommands(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedOperationalStates(Commands* commands, std::string& cmd);

  private:
    CycleControlIntfControllee* m_intfControllee;
    CycleControlListener m_listener;
};

#endif /* CYCLECONTROLLISTENER_H_ */