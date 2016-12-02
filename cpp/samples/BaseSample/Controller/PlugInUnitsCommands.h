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

#ifndef PLUGINUNITSCOMMANDS_H_
#define PLUGINUNITSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfController.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class PlugInUnitsListener : public PlugInUnitsIntfControllerListener{
  public:
    PlugInUnitsListener();
    virtual ~PlugInUnitsListener();

    virtual void OnResponseGetPlugInUnits(QStatus status, const qcc::String& objectPath, const PlugInUnitsInterface::PlugInUnits& units, void* context);
    virtual void OnPlugInUnitsPropertyChanged(const qcc::String& objectPath, const PlugInUnitsInterface::PlugInUnits& units);
};

class PlugInUnitsCommands : public InterfaceCommands
{
  public:
    PlugInUnitsCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~PlugInUnitsCommands();

    virtual void Init();

    PlugInUnitsIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetPlugInUnits(Commands* commands, std::string& cmd);

  private:
    PlugInUnitsIntfController* m_intfController;
    PlugInUnitsListener m_listener;
};


#endif /* PLUGINUNITSCOMMANDS_H_ */