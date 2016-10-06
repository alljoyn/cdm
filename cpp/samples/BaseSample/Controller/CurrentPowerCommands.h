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

#ifndef CURRENTPOWERCOMMANDS_H_
#define CURRENTPOWERCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfController.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentPowerListener : public CurrentPowerIntfControllerListener {
  public:
    CurrentPowerListener();
    virtual ~CurrentPowerListener();
    virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double currentPower, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context);
    virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double currentPower);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime);

};

class CurrentPowerCommands : public InterfaceCommands
{
  public:
    CurrentPowerCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentPowerCommands();

    virtual void Init();

    CurrentPowerIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCurrentPower(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentPowerIntfController* m_intfController;
    CurrentPowerListener m_listener;
};

#endif /* CURRENTPOWERCOMMANDS_H_ */