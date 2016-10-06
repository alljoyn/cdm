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

#ifndef TARGETHUMIDITYCOMMANDS_H_
#define TARGETHUMIDITYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TargetHumidityListener : public TargetHumidityIntfControllerListener {
  public:
    TargetHumidityListener();
    virtual ~TargetHumidityListener();

    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value, void* context);

    virtual void OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMinValueChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const  uint8_t value);
    virtual void OnStepValueChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value);
};

class TargetHumidityCommands : public InterfaceCommands
{
  public:
    TargetHumidityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TargetHumidityCommands();

    virtual void Init();

    TargetHumidityIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);

    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableHumidityLevels(Commands* commands, std::string& cmd);

  private:
    TargetHumidityIntfController* m_intfController;
    TargetHumidityListener m_listener;
};

#endif /* TARGETHUMIDITYCOMMANDS_H_ */