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

#ifndef HIDCOMMANDS_H_
#define HIDCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/input/HidIntfController.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class HidListener : public HidIntfControllerListener {
  public:
    HidListener();
    virtual ~HidListener();
    virtual void OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents, void* context);
    virtual void OnSupportedEventsChanged(const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents);
};

class HidCommands : public InterfaceCommands
{
  public:
    HidCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~HidCommands();

    virtual void Init();

    HidIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetSupportedEvents(Commands* commands, std::string& cmd);
    static void OnCmdInjectGenericEvent(Commands* commands, std::string& cmd);
    static void OnCmdInjectKeyEvent(Commands* commands, std::string& cmd);

  private:
    HidIntfController* m_intfController;
    HidListener m_listener;
};

#endif /* HIDCOMMANDS_H_ */