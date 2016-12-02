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

#ifndef ONOFFSTATUSLISTENER_H_
#define ONOFFSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class OnOffStatusListener : public OnOffStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetIsOn(bool& value);
};

////////////////////////////////////////////////////////////////////////////////

class OnOffStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OnOffStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OnOffStatusCommands();

    virtual void Init();

    OnOffStatusIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetIsOnStatus(Commands* commands, std::string& cmd);
    static void OnCmdSetIsOnStatus(Commands* commands, std::string& cmd);

  private:
    OnOffStatusIntfControllee* m_intfControllee;
    OnOffStatusListener m_listener;
};

#endif /* ONOFFSTATUSLISTENER_H_ */