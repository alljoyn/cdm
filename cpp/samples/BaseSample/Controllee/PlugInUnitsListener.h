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

#ifndef PLUGINUNITSLISTENER_H_
#define PLUGINUNITSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class PlugInUnitsListener : public PlugInUnitsIntfControlleeListener
{
  public:
    virtual QStatus OnGetPlugInUnits(PlugInUnitsInterface::PlugInUnits& plugInUnits);

};

class PlugInUnitsCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    PlugInUnitsCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~PlugInUnitsCommands();

    virtual void Init();
    virtual void InitializeProperties();

    PlugInUnitsIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetPlugInUnits(Commands* commands, std::string& cmd);

  private:
    PlugInUnitsIntfControllee* m_intfControllee;
    PlugInUnitsListener m_listener;
};

#endif /* PLUGINUNITSLISTENER_H_ */