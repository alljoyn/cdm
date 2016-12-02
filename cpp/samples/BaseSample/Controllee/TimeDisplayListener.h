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

#ifndef TIMEDISPLAYLISTENER_H_
#define TIMEDISPLAYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControllee.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TimeDisplayListener : public TimeDisplayIntfControlleeListener
{
  public:

    virtual QStatus OnGetDisplayTimeFormat(uint8_t& timeFormat);

    virtual QStatus OnSetDisplayTimeFormat(const uint8_t timeFormat);

    virtual QStatus OnGetSupportedDisplayTimeFormats(std::vector<uint8_t>& supportedTimeFormats);

    virtual QStatus OnSetSupportedDisplayTimeFormats(const std::vector<uint8_t>& supportedTimeFormats);
};

class TimeDisplayCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TimeDisplayCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TimeDisplayCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TimeDisplayIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetDisplayTimeFormat(Commands* commands, std::string& cmd);
    static void OnCmdSetDisplayTimeFormat(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedDisplayTimeFormats(Commands* commands, std::string& cmd);

  private:
    TimeDisplayIntfControllee* m_intfControllee;
    TimeDisplayListener m_listener;
};




#endif /* TIMEDISPLAYLISTENER_H_ */