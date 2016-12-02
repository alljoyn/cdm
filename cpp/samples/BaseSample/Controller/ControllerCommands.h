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

#ifndef CONTROLLERCOMMAND_H_
#define CONTROLLERCOMMAND_H_

#include <string>
#include "Commands.h"

class ControllerSample;

class ControllerCommands : public Commands {
  public:
      ControllerCommands(ControllerSample* sample);
      virtual ~ControllerCommands();

      virtual void PrintCommands();
      virtual void Execute(std::string& cmd);

      static void OnCmdHelp(Commands* commands, std::string& cmd);
      static void OnCmdBack(Commands* commands, std::string& cmd);
      static void OnCmdQuit(Commands* commands, std::string& cmd);

      ControllerSample* GetControllerSample() { return m_sample; }
  protected:
      ControllerSample* m_sample;
};


#endif // CONTROLLERCOMMAND_H_
