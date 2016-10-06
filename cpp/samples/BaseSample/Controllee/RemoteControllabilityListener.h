/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef REMOTECONTROLLABILITYLISTENER_H_
#define REMOTECONTROLLABILITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class RemoteControllabilityListener : public RemoteControllabilityIntfControlleeListener
{
  public:
    virtual QStatus OnGetIsControllable(bool& isControllable);
};


class RemoteControllabilityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RemoteControllabilityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RemoteControllabilityCommands();

    virtual void Init();

    RemoteControllabilityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetIsControllable(Commands* commands, std::string& cmd);
    static void OnCmdSetIsControllable(Commands* commands, std::string& cmd);

  private:
    RemoteControllabilityIntfControllee* m_intfControllee;
    RemoteControllabilityListener m_listener;
};


#endif /* REMOTECONTROLLABILITYLISTENER_H_ */