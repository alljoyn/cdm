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

#ifndef OFFCONTROLLISTENER_H_
#define OFFCONTROLLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class OffControlListener : public OffControlIntfControlleeListener
{
  public:
    virtual QStatus OnSwitchOff(ErrorCode& errorCode);
};
////////////////////////////////////////////////////////////////////////////////

class OffControlCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OffControlCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OffControlCommands();

    virtual void Init();

    OffControlIntfControllee* GetInterface() { return m_intfControllee; }

  private:
    OffControlIntfControllee* m_intfControllee;
    OffControlListener m_listener;
};


#endif /* OFFCONTROLLISTENER_H_ */