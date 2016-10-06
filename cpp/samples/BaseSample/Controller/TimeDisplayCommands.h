/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef TIMEDISPLAYCOMMANDS_H_
#define TIMEDISPLAYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TimeDisplayListener : public TimeDisplayIntfControllerListener {
  public:
    TimeDisplayListener();
    virtual ~TimeDisplayListener();

    virtual void GetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t timeformat, void* context);

    virtual void SetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

    virtual void GetSupportedDisplayTimeFormatsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats, void* context);

    virtual void DisplayTimeFormatPropertyChanged(const qcc::String& objectPath, const uint8_t timeformat);

    virtual void SupportedDisplayTimeFormatsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats);
};

class TimeDisplayCommands : public InterfaceCommands
{
  public:
    TimeDisplayCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TimeDisplayCommands();

    virtual void Init();

    TimeDisplayIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetDisplayTimeFormat(Commands* commands, std::string& cmd);
    static void OnCmdSetDisplayTimeFormat(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedDisplayTimeFormats(Commands* commands, std::string& cmd);

  private:
    TimeDisplayIntfController* m_intfController;
    TimeDisplayListener m_listener;
};


#endif /* SOILLEVELCOMMANDS_H_ */