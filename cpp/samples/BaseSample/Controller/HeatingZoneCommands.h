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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef HEATINGZONECOMMANDS_H_
#define HEATINGZONECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfController.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class HeatingZoneListener : public HeatingZoneIntfControllerListener{
  public:
    HeatingZoneListener();
    virtual ~HeatingZoneListener();

    virtual void OnGetNumberOfHeatingZonesPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t numberOfZones, void* context);
    virtual void OnGetMaxHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels, void* context);
    virtual void OnGetHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels, void* context);
    virtual void NumberOfHeatingZonesPropertyChanged(const qcc::String& objectPath, const uint8_t numberOfHeatingZones);
    virtual void MaxHeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels);
    virtual void HeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels);
};

class HeatingZoneCommands : public InterfaceCommands
{
  public:
    HeatingZoneCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~HeatingZoneCommands();

    virtual void Init();

    HeatingZoneIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetNumberOfHeatingZones(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxHeatingLevels(Commands* commands, std::string& cmd);

    static void OnCmdGetHeatingLevels(Commands* commands, std::string& cmd);
  private:
    HeatingZoneIntfController* m_intfController;
    HeatingZoneListener m_listener;
};


#endif /* HEATINGZONECOMMANDS_H_ */