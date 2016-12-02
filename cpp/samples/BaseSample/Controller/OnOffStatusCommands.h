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

#ifndef ONOFFSTATUSCOMMANDS_H_
#define ONOFFSTATUSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class OnOffStatusListener : public OnOffStatusIntfControllerListener {
  public:
    OnOffStatusListener();
    virtual ~OnOffStatusListener();
    virtual void OnResponseGetIsOn(QStatus status, const qcc::String& objectPath, const bool value, void* context);
    virtual void OnIsOnChanged(const qcc::String& objectPath, const bool value);
};

class OnOffStatusCommands : public InterfaceCommands
{
  public:
    OnOffStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~OnOffStatusCommands();

    virtual void Init();

    OnOffStatusIntfController* GetInterface() { return m_intfController; }

    static void OnCmdOnOffStatus(Commands* commands, std::string& cmd);

  private:
    OnOffStatusIntfController* m_intfController;
    OnOffStatusListener m_listener;
};

#endif /* ONOFFSTATUSCOMMANDS_H_ */