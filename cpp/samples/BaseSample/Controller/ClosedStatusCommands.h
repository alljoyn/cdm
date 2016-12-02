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

#ifndef CLOSEDSTATUSCOMMANDS_H_
#define CLOSEDSTATUSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class ClosedStatusListener : public ClosedStatusIntfControllerListener{
  public:
    ClosedStatusListener();
    virtual ~ClosedStatusListener();
    virtual void IsClosedPropertyChanged(const qcc::String& objectPath, const bool isClosed);
    virtual void GetIsClosedPropertyCallback(QStatus status, const qcc::String& objectPath, const bool isClosed, void* context);
};

class ClosedStatusCommands : public InterfaceCommands
{
  public:
    ClosedStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~ClosedStatusCommands();

    virtual void Init();

    ClosedStatusIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetIsClosed(Commands* commands, std::string& cmd);

  private:
    ClosedStatusIntfController* m_intfController;
    ClosedStatusListener m_listener;
};


#endif /* CLOSEDSTATUSCOMMANDS_H_ */