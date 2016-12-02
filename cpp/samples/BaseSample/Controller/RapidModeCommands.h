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

#ifndef RAPIDMODECOMMANDS_H_
#define RAPIDMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RapidModeListener : public RapidModeIntfControllerListener{
  public:
    RapidModeListener();
    virtual ~RapidModeListener();
    virtual void RapidModePropertyChanged(const qcc::String& objectPath, const bool rapidMode);
    virtual void OnGetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, const bool rapidMode, void* context);
    virtual void OnSetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

};

class RapidModeCommands : public InterfaceCommands
{
  public:
    RapidModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RapidModeCommands();

    virtual void Init();

    RapidModeIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetRapidMode(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidMode(Commands* commands, std::string& cmd);

  private:
    RapidModeIntfController* m_intfController;
    RapidModeListener m_listener;
};


#endif /* RAPIDMODECOMMANDS_H_ */