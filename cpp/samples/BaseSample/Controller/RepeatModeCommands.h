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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef REPEATMODECOMMANDS_H_
#define REPEATMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RepeatModeListener : public RepeatModeIntfControllerListener {
  public:
    RepeatModeListener();
    virtual ~RepeatModeListener();
    virtual void OnResponseGetRepeatMode(QStatus status, const qcc::String& objectPath, const bool repeatMode, void* context);
    virtual void OnResponseSetRepeatMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnRepeatModeChanged(const qcc::String& objectPath, const bool value);

};

class RepeatModeCommands : public InterfaceCommands
{
  public:
    RepeatModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RepeatModeCommands();

    virtual void Init();

    RepeatModeIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetRepeatMode(Commands* commands, std::string& cmd);
    static void OnCmdSetRepeatMode(Commands* commands, std::string& cmd);

  private:
    RepeatModeIntfController* m_intfController;
    RepeatModeListener m_listener;
};

#endif /* REPEATMODECOMMANDS_H_ */