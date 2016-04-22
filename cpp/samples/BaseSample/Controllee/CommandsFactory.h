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

#ifndef COMMANDSFACTORY_H_
#define COMMANDSFACTORY_H_

#include <map>
#include <qcc/String.h>

#include <alljoyn/hae/interfaces/HaeInterface.h>
#include <alljoyn/hae/interfaces/HaeInterfaceListener.h>
#include "ControlleeCommands.h"

namespace ajn {
class BusAttachment;
namespace services {

class CommandsFactory {
  public:
    static CommandsFactory* GetInstance();
    ~CommandsFactory() {}

    ControlleeCommands* CreateCommands(const HaeInterfaceType type, ControlleeSample* sample, const char* objectPath);

    void RegisterCreator(const HaeInterfaceType type, CreateCommandsFptr fptr);

  private:
    CommandsFactory();
    CommandsFactory(const CommandsFactory& src);
    CommandsFactory& operator=(const CommandsFactory& src);

    static CommandsFactory* s_instance;
    std::map<HaeInterfaceType, CreateCommandsFptr> m_creators;
};

} //namespace services
} //namespace ajn

#endif // COMMANDSFACTORY_H_
