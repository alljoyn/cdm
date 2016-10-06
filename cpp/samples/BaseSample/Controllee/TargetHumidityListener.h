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

#ifndef TARGETHUMIDITYLISTENER_H_
#define TARGETHUMIDITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TargetHumidityListener : public TargetHumidityIntfControlleeListener
{
  public:
    virtual QStatus OnSetTargetValue(const uint8_t value);
    virtual QStatus OnGetTargetValue(uint8_t& value);
    virtual QStatus OnGetMinValue(uint8_t& value);
    virtual QStatus OnGetMaxValue(uint8_t& value);
    virtual QStatus OnGetStepValue(uint8_t& value);
    virtual QStatus OnGetSelectableHumidityLevels(TargetHumidityInterface::HumidityLevels& value);
};

class TargetHumidityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TargetHumidityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TargetHumidityCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TargetHumidityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdSetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableHumidityLevels(Commands* commands, std::string& cmd);
    static void OnCmdSetSelectableHumidityLevels(Commands* commands, std::string& cmd);

  private:
    TargetHumidityIntfControllee* m_intfControllee;
    TargetHumidityListener m_listener;
};



#endif /* TARGETHUMIDITYLISTENER_H_ */