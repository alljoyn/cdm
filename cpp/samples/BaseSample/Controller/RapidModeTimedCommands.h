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

#ifndef RAPIDMODETIMEDCOMMANDS_H_
#define RAPIDMODETIMEDCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RapidModeTimedListener : public RapidModeTimedIntfControllerListener {
  public:
    RapidModeTimedListener();
    virtual ~RapidModeTimedListener();

    virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value);

    virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
};

class RapidModeTimedCommands : public InterfaceCommands
{
  public:
    RapidModeTimedCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RapidModeTimedCommands();

    virtual void Init();

    RapidModeTimedIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxSetMinutes(Commands* commands, std::string& cmd);

  private:
    RapidModeTimedIntfController* m_intfController;
    RapidModeTimedListener m_listener;
};

#endif /* RAPIDMODETIMEDCOMMANDS_H_ */