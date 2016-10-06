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

#ifndef RAPIDMODETIMEDLISTENER_H_
#define RAPIDMODETIMEDLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class RapidModeTimedListener : public RapidModeTimedIntfControlleeListener
{
  public:
    virtual QStatus OnGetRapidModeMinutesRemaining(uint16_t& value);
    virtual QStatus OnSetRapidModeMinutesRemaining(const uint16_t& value);
    virtual QStatus OnGetMaxSetMinutes(uint16_t& value);
};

class RapidModeTimedCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RapidModeTimedCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RapidModeTimedCommands();

    virtual void Init();
    virtual void InitializeProperties();

    RapidModeTimedIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxSetMinutes(Commands* commands, std::string& cmd);

  private:
    RapidModeTimedIntfControllee* m_intfControllee;
    RapidModeTimedListener m_listener;
};

#endif /* RAPIDMODETIMEDLISTENER_H_ */