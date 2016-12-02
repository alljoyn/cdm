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

#ifndef RAPIDMODETIMEDLISTENER_H_
#define RAPIDMODETIMEDLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class RapidModeTimedListener : public RapidModeTimedIntfControlleeListener
{
  public:
    virtual QStatus OnGetRapidModeMinutesRemaining(uint16_t& value);
    virtual QStatus OnSetRapidModeMinutesRemaining(const uint16_t& value);
    virtual QStatus OnGetMaxSetMinutes(uint16_t& value);
};

class RapidModeTimedCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RapidModeTimedCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RapidModeTimedCommands();

    virtual void Init();
    virtual void InitializeProperties();

    RapidModeTimedIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxSetMinutes(Commands* commands, std::string& cmd);

  private:
    RapidModeTimedIntfControllee* m_intfControllee;
    RapidModeTimedListener m_listener;
};

#endif /* RAPIDMODETIMEDLISTENER_H_ */