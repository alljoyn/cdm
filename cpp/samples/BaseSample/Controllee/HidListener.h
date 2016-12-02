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

#ifndef HIDLISTENER_H_
#define HIDLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/input/HidIntfControllee.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class HidListener : public HidIntfControlleeListener
{
  public:
    virtual QStatus OnGetSupportedEvents(HidInterface::SupportedInputEvents& supportedEvents);
    virtual void OnInjectEvents(HidInterface::InputEvents& inputEvents);
};

////////////////////////////////////////////////////////////////////////////////////////////
class HidCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    HidCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~HidCommands();

    virtual void Init();
    virtual void InitializeProperties();
    HidIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetSupportedEvents(Commands* commands, std::string& cmd);

  private:
    HidIntfControllee* m_intfControllee;
    HidListener m_listener;
};

#endif /* HIDLISTENER_H_ */