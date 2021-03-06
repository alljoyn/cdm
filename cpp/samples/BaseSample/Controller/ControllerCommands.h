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

