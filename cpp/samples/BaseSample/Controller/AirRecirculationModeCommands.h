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

#ifndef AIRRECIRCULATIONMODECOMMANDS_H_
#define AIRRECIRCULATIONMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class AirRecirculationModeListener : public AirRecirculationModeIntfControllerListener {
  public:
    AirRecirculationModeListener();
    virtual ~AirRecirculationModeListener();
    virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context);
    virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating);
};

class AirRecirculationModeCommands : public InterfaceCommands
{
  public:
    AirRecirculationModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~AirRecirculationModeCommands();

    virtual void Init();

    AirRecirculationModeIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetIsRecirculating(Commands* commands, std::string& cmd);
    static void OnCmdSetIsRecirculating(Commands* commands, std::string& cmd);

  private:
    AirRecirculationModeIntfController* m_intfController;
    AirRecirculationModeListener m_listener;
};

#endif /* AIRRECIRCULATIONMODECOMMANDS_H_ */