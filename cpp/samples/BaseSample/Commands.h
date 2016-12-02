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

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <map>
#include <list>

class Commands;

typedef void (*CommandFunc)(Commands*, std::string&);
typedef struct CommandItem_t {
    std::string command;
    std::string description;
    CommandFunc func;
}CommandItem;

typedef std::map<std::string, CommandItem> CommandFuncMap;
typedef std::map<std::string, Commands*> ChildCommandMap;

class Commands {
  public:
      Commands();
      virtual ~Commands();

      bool RegisterCommand(CommandFunc func, const std::string& name, const std::string& description);
      bool RegisterChildCommands(const std::string& key, Commands* commands);
      Commands* GetChild(const std::string& key);
      ChildCommandMap& GetChildren();

      virtual void Init() = 0;
      virtual void PrintCommands() = 0;
      virtual void Execute(std::string& cmd) = 0;

  protected:
      void PrintCommandList();

      static std::string GetCommandToken(std::string& cmd, std::string& remain);
      static int GetCommandTokenInt(std::string& cmd, std::string& remain);
      static int ReadIndex();

  protected:
      std::string m_CommandText;
      CommandFuncMap m_Commands;
      ChildCommandMap m_Children;
};

#endif // COMMAND_H_
