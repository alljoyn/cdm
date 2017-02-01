/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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

#ifndef CURRENTAIRQUALITYLEVELLISTENER_H_
#define CURRENTAIRQUALITYLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentAirQualityLevelListener : public CurrentAirQualityLevelIntfControlleeListener
{
  public:
    virtual QStatus OnGetContaminantType(uint8_t& type);
    virtual QStatus OnGetCurrentLevel(uint8_t& value);
    virtual QStatus OnGetMaxLevel(uint8_t& value);
};

class CurrentAirQualityLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentAirQualityLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentAirQualityLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CurrentAirQualityLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdSetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityLevelIntfControllee* m_intfControllee;
    CurrentAirQualityLevelListener m_listener;
};



#endif /* CURRENTAIRQUALITYLEVELLISTENER_H_ */