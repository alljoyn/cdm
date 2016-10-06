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

#ifndef TARGETTEMPERATURELEVELCOMMANDS_H_
#define TARGETTEMPERATURELEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TargetTemperatureLevelListener : public TargetTemperatureLevelIntfControllerListener {
  public:
    TargetTemperatureLevelListener();
    virtual ~TargetTemperatureLevelListener();

    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value, void* context);

    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const  uint8_t value);
    virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value);
};

class TargetTemperatureLevelCommands : public InterfaceCommands
{
  public:
    TargetTemperatureLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TargetTemperatureLevelCommands();

    virtual void Init();

    TargetTemperatureLevelIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableTemperatureLevels(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureLevelIntfController* m_intfController;
    TargetTemperatureLevelListener m_listener;
};

#endif /* TARGETTEMPERATURELEVELCOMMANDS_H_ */