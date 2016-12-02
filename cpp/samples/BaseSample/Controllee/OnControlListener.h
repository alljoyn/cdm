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

#ifndef ONCONTROLLISTENER_H_
#define ONCONTROLLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class OnControlListener : public OnControlIntfControlleeListener
{
  public:
    virtual QStatus OnSwitchOn(ErrorCode& errorCode);
};
////////////////////////////////////////////////////////////////////////////////

class OnControlCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OnControlCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OnControlCommands();

    virtual void Init();

    OnControlIntfControllee* GetInterface() { return m_intfControllee; }

  private:
    OnControlIntfControllee* m_intfControllee;
    OnControlListener m_listener;
};

#endif /* ONCONTROLLISTENER_H_ */