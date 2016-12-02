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

#ifndef CLOSEDSTATUSLISTENER_H_
#define CLOSEDSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class ClosedStatusListener : public ClosedStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetIsClosed(bool& isClosed);
};

class ClosedStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    ClosedStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~ClosedStatusCommands();

    virtual void Init();

    ClosedStatusIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetClosedStatus(Commands* commands, std::string& cmd);
    static void OnCmdSetClosedStatus(Commands* commands, std::string& cmd);

  private:
    ClosedStatusIntfControllee* m_intfControllee;
    ClosedStatusListener m_listener;
};


#endif /* CLOSEDSTATUSLISTENER_H_ */
