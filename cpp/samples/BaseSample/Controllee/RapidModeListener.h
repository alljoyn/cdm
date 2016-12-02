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

#ifndef RAPIDMODELISTENER_H_
#define RAPIDMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class RapidModeListener : public RapidModeIntfControlleeListener
{
  public:

    virtual QStatus OnSetRapidMode(const bool& rapidMode);

    virtual QStatus OnGetRapidMode(bool& rapidMode);
};

class RapidModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RapidModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RapidModeCommands();

    virtual void Init();

    RapidModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetRapidMode(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidMode(Commands* commands, std::string& cmd);

  private:
    RapidModeIntfControllee* m_intfControllee;
    RapidModeListener m_listener;

};
#endif /* RAPIDMODELISTENER_H_ */