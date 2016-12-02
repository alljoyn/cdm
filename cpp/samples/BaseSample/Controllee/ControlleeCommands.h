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

#ifndef CONTROLLEECOMMAND_H_
#define CONTROLLEECOMMAND_H_

#include <string>
#include "Commands.h"

class ControlleeSample;
class ControlleeCommands;

typedef ControlleeCommands* (*CreateCommandsFptr)(ControlleeSample*, const char* objectPath);

class ControlleeCommands : public Commands {
  public:
      ControlleeCommands(ControlleeSample* sample);
      virtual ~ControlleeCommands();

      virtual void Init();
      virtual void PrintCommands();
      virtual void Execute(std::string& cmd);
      virtual void InitializeProperties();

      static void OnCmdHelp(Commands* commands, std::string& cmd);
      static void OnCmdBack(Commands* commands, std::string& cmd);
      static void OnCmdQuit(Commands* commands, std::string& cmd);

      ControlleeSample* GetControlleeSample() { return m_sample; }
  protected:
      ControlleeSample* m_sample;
};


#endif // CONTROLLEECOMMAND_H_
