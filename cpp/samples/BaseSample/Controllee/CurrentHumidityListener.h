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

#ifndef CURRENTHUMIDITYLISTENER_H_
#define CURRENTHUMIDITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentHumidityListener : public CurrentHumidityIntfControlleeListener
{
  public:
    virtual QStatus OnGetCurrentValue(uint8_t& value);
    virtual QStatus OnGetMaxValue(uint8_t& value);
};

class CurrentHumidityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentHumidityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentHumidityCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CurrentHumidityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);

  private:
    CurrentHumidityIntfControllee* m_intfControllee;
    CurrentHumidityListener m_listener;
};

#endif /* CURRENTHUMIDITYLISTENER_H_ */