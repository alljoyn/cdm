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

#ifndef WINDDIRECTIONCOMMANDS_H_
#define WINDDIRECTIONCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfController.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class WindDirectionListener : public WindDirectionIntfControllerListener {
  public:
    WindDirectionListener();
    virtual ~WindDirectionListener();

    virtual void OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);

    virtual void OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnHorizontalAutoModeChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnVerticalAutoModeChanged(const qcc::String& objectPath, const uint8_t value);

};


class WindDirectionCommands : public InterfaceCommands
{
  public:
    WindDirectionCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~WindDirectionCommands();

    virtual void Init();

    WindDirectionIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetHorizontalDirection(Commands* commands, std::string& cmd);
    static void OnCmdSetHorizontalDirection(Commands* commands, std::string& cmd);
    static void OnCmdGetHorizontalMax(Commands* commands, std::string& cmd);
    static void OnCmdGetHorizontalAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetHorizontalAutoMode(Commands* commands, std::string& cmd);

    static void OnCmdGetVerticalDirection(Commands* commands, std::string& cmd);
    static void OnCmdSetVerticalDirection(Commands* commands, std::string& cmd);
    static void OnCmdGetVerticalMax(Commands* commands, std::string& cmd);
    static void OnCmdGetVerticalAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetVerticalAutoMode(Commands* commands, std::string& cmd);

  private:
    WindDirectionIntfController* m_intfController;
    WindDirectionListener m_listener;
};

#endif /* WINDDIRECTIONCOMMANDS_H_ */