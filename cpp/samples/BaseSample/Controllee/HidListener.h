/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef HIDLISTENER_H_
#define HIDLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/input/HidIntfControllee.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class HidListener : public HidIntfControlleeListener
{
  public:
    virtual QStatus OnGetSupportedEvents(HidInterface::SupportedInputEvents& supportedEvents);
    virtual void OnInjectEvents(HidInterface::InputEvents& inputEvents);
};

////////////////////////////////////////////////////////////////////////////////////////////
class HidCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    HidCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~HidCommands();

    virtual void Init();
    virtual void InitializeProperties();
    HidIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetSupportedEvents(Commands* commands, std::string& cmd);

  private:
    HidIntfControllee* m_intfControllee;
    HidListener m_listener;
};

#endif /* HIDLISTENER_H_ */