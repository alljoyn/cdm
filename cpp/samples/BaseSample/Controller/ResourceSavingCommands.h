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

#ifndef RESOURCESAVINGCOMMANDS_H_
#define RESOURCESAVINGCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class ResourceSavingListener : public ResourceSavingIntfControllerListener {
  public:
    ResourceSavingListener();
    virtual ~ResourceSavingListener();

    virtual void OnResponseSetResourceSavingMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetResourceSavingMode(QStatus status, const qcc::String& objectPath, const bool value, void* context);
    virtual void OnResourceSavingModeChanged(const qcc::String& objectPath, const bool value);
};


class ResourceSavingCommands : public InterfaceCommands
{
  public:
    ResourceSavingCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~ResourceSavingCommands();

    virtual void Init();

    ResourceSavingIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetResourceSavingMode(Commands* commands, std::string& cmd);
    static void OnCmdSetResourceSavingMode(Commands* commands, std::string& cmd);

  private:
    ResourceSavingIntfController* m_intfController;
    ResourceSavingListener m_listener;
};

#endif /* RESOURCESAVINGCOMMANDS_H_ */