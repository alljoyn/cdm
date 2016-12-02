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

#ifndef RESOURCESAVINGLISTENER_H_
#define RESOURCESAVINGLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class ResourceSavingListener : public ResourceSavingIntfControlleeListener
{
  public:
    virtual QStatus OnSetResourceSavingMode(const bool& mode);
    virtual QStatus OnGetResourceSavingMode(bool& mode);
};
////////////////////////////////////////////////////////////////////////////////

class ResourceSavingCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    ResourceSavingCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~ResourceSavingCommands();

    virtual void Init();

    ResourceSavingIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetResourceSavingMode(Commands* commands, std::string& cmd);
    static void OnCmdSetResourceSavingMode(Commands* commands, std::string& cmd);

  private:
    ResourceSavingIntfControllee* m_intfControllee;
    ResourceSavingListener m_listener;
};


#endif /* RESOURCESAVINGLISTENER_H_ */