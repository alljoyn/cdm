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

#ifndef AIRRECIRCULATIONMODELISTENER_H_
#define AIRRECIRCULATIONMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class AirRecirculationModeListener : public AirRecirculationModeIntfControlleeListener
{
  public:
    virtual QStatus OnSetIsRecirculating(const bool& isRecirculating);
    virtual QStatus OnGetIsRecirculating(bool& isRecirculating);
};

class AirRecirculationModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    AirRecirculationModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~AirRecirculationModeCommands();

    virtual void Init();

    AirRecirculationModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetIsRecirculating(Commands* commands, std::string& cmd);
    static void OnCmdSetIsRecirculating(Commands* commands, std::string& cmd);

  private:
    AirRecirculationModeIntfControllee* m_intfControllee;
    AirRecirculationModeListener m_listener;
};


#endif /* AIRRECIRCULATIONMODELISTENER_H_ */