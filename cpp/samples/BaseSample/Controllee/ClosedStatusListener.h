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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef CLOSEDSTATUSLISTENER_H_
#define CLOSEDSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class ClosedStatusListener : public ClosedStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetIsClosed(bool& isClosed);
};

class ClosedStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    ClosedStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~ClosedStatusCommands();

    virtual void Init();

    ClosedStatusIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetClosedStatus(Commands* commands, std::string& cmd);
    static void OnCmdSetClosedStatus(Commands* commands, std::string& cmd);

  private:
    ClosedStatusIntfControllee* m_intfControllee;
    ClosedStatusListener m_listener;
};


#endif /* CLOSEDSTATUSLISTENER_H_ */
