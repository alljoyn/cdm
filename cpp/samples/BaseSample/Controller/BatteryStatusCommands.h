/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef BATTERYSTATUSCOMMANDS_H_
#define BATTERYSTATUSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class BatteryStatusListener : public BatteryStatusIntfControllerListener {
  public:
    BatteryStatusListener();
    virtual ~BatteryStatusListener();
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t currentValue, void* context);
    virtual void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool isCharging, void* context);
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t currentValue);
    virtual void OnIsChargingChanged(const qcc::String& objectPath, const bool isCharging);
};

class BatteryStatusCommands : public InterfaceCommands
{
  public:
    BatteryStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~BatteryStatusCommands();

    virtual void Init();

    BatteryStatusIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetIsCharging(Commands* commands, std::string& cmd);

  private:
    BatteryStatusIntfController* m_intfController;
    BatteryStatusListener m_listener;
};

#endif /* BATTERYSTATUSCOMMANDS_H_ */