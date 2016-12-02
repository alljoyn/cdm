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

#ifndef COMMANDSFACTORY_H_
#define COMMANDSFACTORY_H_

#include <map>
#include <qcc/String.h>

#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceListener.h>
#include "ControlleeCommands.h"

namespace ajn {
class BusAttachment;
namespace services {

class CommandsFactory {
  public:
    static CommandsFactory* GetInstance();
    ~CommandsFactory() {}

    ControlleeCommands* CreateCommands(const CdmInterfaceType type, ControlleeSample* sample, const char* objectPath);

    void RegisterCreator(const CdmInterfaceType type, CreateCommandsFptr fptr);

  private:
    CommandsFactory();
    CommandsFactory(const CommandsFactory& src);
    CommandsFactory& operator=(const CommandsFactory& src);

    static CommandsFactory* s_instance;
    std::map<CdmInterfaceType, CreateCommandsFptr> m_creators;
};

} //namespace services
} //namespace ajn

#endif // COMMANDSFACTORY_H_