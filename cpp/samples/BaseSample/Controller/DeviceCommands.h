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

#ifndef DEVICECOMMANDS_H_
#define DEVICECOMMANDS_H_

#include "ControllerCommands.h"
#include <alljoyn/cdm/DeviceInfo.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class DeviceCommands : public ControllerCommands
{
  public:
    DeviceCommands(ControllerSample* sample, DeviceInfoPtr& info);
    virtual ~DeviceCommands();

    virtual void Init();

    ControllerSample* GetControllerSample() { return m_sample; }
    DeviceInfoPtr& GetDeviceInfo() { return m_deviceInfo; }
    static void OnCmdSelectInterface(Commands* commands, std::string&);
    static void OnCmdBack(Commands* commands, std::string& cmd);

  private:
    ControllerSample* m_sample;
    DeviceInfoPtr m_deviceInfo;

    static Commands* CreateInterfaceCommands(Commands* commands, const char* intfName, const char* objectPath);
};


#endif