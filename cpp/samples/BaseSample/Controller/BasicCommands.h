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

#ifndef BASICCOMMANDS_H_
#define BASICCOMMANDS_H_

#include "ControllerCommands.h"

class ControllerSample;

class BasicControllerCommands : public ControllerCommands
{
  public:
    BasicControllerCommands(ControllerSample* sample);
    virtual ~BasicControllerCommands();

    virtual void Init();
    static void OnCmdDeviceList(Commands* commands, std::string&);
    static void OnCmdDeviceInfo(Commands* commands, std::string&);
    static void OnCmdDeviceJoin(Commands* commands, std::string&);

  private:
    static void PrintAboutData(ajn::services::CdmAboutData& aboutData);
    static void PrintAboutObjectDescription(ajn::AboutObjectDescription& aboutObjectDesc);
};

#endif