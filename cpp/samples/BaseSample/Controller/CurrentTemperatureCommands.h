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

#ifndef CURRENTTEMPERATURECOMMANDS_H_
#define CURRENTTEMPERATURECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentTemperatureListener : public CurrentTemperatureIntfControllerListener {
  public:
    CurrentTemperatureListener();
    virtual ~CurrentTemperatureListener();

    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context);
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime);
};

class CurrentTemperatureCommands : public InterfaceCommands
{
  public:
    CurrentTemperatureCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentTemperatureCommands();

    virtual void Init();

    CurrentTemperatureIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentTemperatureIntfController* m_intfController;
    CurrentTemperatureListener m_listener;
};

#endif /* CURRENTTEMPERATURECOMMANDS_H_ */