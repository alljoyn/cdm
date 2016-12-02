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

#ifndef REPEATMODECOMMANDS_H_
#define REPEATMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RepeatModeListener : public RepeatModeIntfControllerListener {
  public:
    RepeatModeListener();
    virtual ~RepeatModeListener();
    virtual void OnResponseGetRepeatMode(QStatus status, const qcc::String& objectPath, const bool repeatMode, void* context);
    virtual void OnResponseSetRepeatMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnRepeatModeChanged(const qcc::String& objectPath, const bool value);

};

class RepeatModeCommands : public InterfaceCommands
{
  public:
    RepeatModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RepeatModeCommands();

    virtual void Init();

    RepeatModeIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetRepeatMode(Commands* commands, std::string& cmd);
    static void OnCmdSetRepeatMode(Commands* commands, std::string& cmd);

  private:
    RepeatModeIntfController* m_intfController;
    RepeatModeListener m_listener;
};

#endif /* REPEATMODECOMMANDS_H_ */