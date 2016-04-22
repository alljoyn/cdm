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

#include <qcc/Debug.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/LogModule.h>
#include "CommandsFactory.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CommandsFactory* CommandsFactory::s_instance(0);

CommandsFactory* CommandsFactory::GetInstance()
{
    if (!s_instance) {
        s_instance = new CommandsFactory();
    }
    return s_instance;
}

CommandsFactory::CommandsFactory()
{
}

CommandsFactory::CommandsFactory(const CommandsFactory& src)
{
}

CommandsFactory& CommandsFactory::operator=(const CommandsFactory& src)
{
    return *this;
}

ControlleeCommands* CommandsFactory::CreateCommands(const HaeInterfaceType type, ControlleeSample* sample, const char* objectPath)
{
    ControlleeCommands* commands = NULL;
    if (m_creators.find(type) != m_creators.end()) {
        commands = m_creators[type](sample, objectPath);
    }
    if (!commands) {
        return NULL;
    }

    return  commands;
}

void CommandsFactory::RegisterCreator(const HaeInterfaceType type, CreateCommandsFptr fptr)
{
    m_creators[type] = fptr;
}

}
}
