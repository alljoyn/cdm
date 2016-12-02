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

#include <qcc/Debug.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/LogModule.h>
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

ControlleeCommands* CommandsFactory::CreateCommands(const CdmInterfaceType type, ControlleeSample* sample, const char* objectPath)
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

void CommandsFactory::RegisterCreator(const CdmInterfaceType type, CreateCommandsFptr fptr)
{
    m_creators[type] = fptr;
}

}
}