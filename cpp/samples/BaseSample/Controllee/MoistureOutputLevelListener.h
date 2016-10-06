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

#ifndef MOISTUREOUTPUTLEVELLISTENER_H_
#define MOISTUREOUTPUTLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class MoistureOutputLevelListener : public MoistureOutputLevelIntfControlleeListener
{
  public:
    virtual QStatus OnSetMoistureOutputLevel(const uint8_t& value);
    virtual QStatus OnGetMoistureOutputLevel(uint8_t& value);
    virtual QStatus OnGetMaxMoistureOutputLevel(uint8_t& value);
    virtual QStatus OnSetAutoMode(const uint8_t& autoMode);
    virtual QStatus OnGetAutoMode(uint8_t& autoMode);
};

class MoistureOutputLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    MoistureOutputLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~MoistureOutputLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    MoistureOutputLevelIntfControllee* GetInterface() { return m_intfControllee; }

    static void OnCmdGetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    MoistureOutputLevelIntfControllee* m_intfControllee;
    MoistureOutputLevelListener m_listener;
};

#endif /* MOISTUREOUTPUTLEVELLISTENER_H_ */