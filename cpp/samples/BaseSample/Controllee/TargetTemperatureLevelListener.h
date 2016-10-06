/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TARGETTEMPERATURELEVELLISTENER_H_
#define TARGETTEMPERATURELEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TargetTemperatureLevelListener : public TargetTemperatureLevelIntfControlleeListener
{
  public:
    virtual QStatus OnSetTargetLevel(const uint8_t value);
    virtual QStatus OnGetTargetLevel(uint8_t& value);
    virtual QStatus OnGetMaxLevel(uint8_t& value);
    virtual QStatus OnGetSelectableTemperatureLevels(TargetTemperatureLevelInterface::TemperatureLevels& value);
};

class TargetTemperatureLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TargetTemperatureLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TargetTemperatureLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TargetTemperatureLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableTemperatureLevels(Commands* commands, std::string& cmd);
    static void OnCmdSetSelectableTemperatureLevels(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureLevelIntfControllee* m_intfControllee;
    TargetTemperatureLevelListener m_listener;
};

#endif /* TARGETTEMPERATURELEVELLISTENER_H_ */