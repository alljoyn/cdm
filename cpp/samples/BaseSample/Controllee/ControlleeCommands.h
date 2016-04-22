/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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

