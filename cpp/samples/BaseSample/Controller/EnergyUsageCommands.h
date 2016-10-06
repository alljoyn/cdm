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

#ifndef ENERGYUSAGECOMMANDS_H_
#define ENERGYUSAGECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfController.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class EnergyUsageListener : public EnergyUsageIntfControllerListener {
  public:
    EnergyUsageListener();
    virtual ~EnergyUsageListener();
    virtual void OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double cumulativeEnergy, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context);
    virtual void OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath,
                                                 void* context, const char* errorName, const char* errorMessage);
    virtual void OnCumulativeEnergyChanged(const qcc::String& objectPath, const double cumulativeEnergy);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime);
};

class EnergyUsageCommands : public InterfaceCommands
{
  public:
    EnergyUsageCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~EnergyUsageCommands();

    virtual void Init();

    EnergyUsageIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetCumulativeEnergy(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdResetCumulativeEnergy(Commands* commands, std::string& cmd);

  private:
    EnergyUsageIntfController* m_intfController;
    EnergyUsageListener m_listener;
};

#endif /* ENERGYUSAGECOMMANDS_H_ */