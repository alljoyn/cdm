/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
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