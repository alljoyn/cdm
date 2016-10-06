/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
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
