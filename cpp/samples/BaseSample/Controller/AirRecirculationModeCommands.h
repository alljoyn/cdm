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

#ifndef AIRRECIRCULATIONMODECOMMANDS_H_
#define AIRRECIRCULATIONMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class AirRecirculationModeListener : public AirRecirculationModeIntfControllerListener {
  public:
    AirRecirculationModeListener();
    virtual ~AirRecirculationModeListener();
    virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context);
    virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating);
};

class AirRecirculationModeCommands : public InterfaceCommands
{
  public:
    AirRecirculationModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~AirRecirculationModeCommands();

    virtual void Init();

    AirRecirculationModeIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetIsRecirculating(Commands* commands, std::string& cmd);
    static void OnCmdSetIsRecirculating(Commands* commands, std::string& cmd);

  private:
    AirRecirculationModeIntfController* m_intfController;
    AirRecirculationModeListener m_listener;
};

#endif /* AIRRECIRCULATIONMODECOMMANDS_H_ */