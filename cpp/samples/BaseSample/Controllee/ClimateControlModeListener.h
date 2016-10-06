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

#ifndef CLIMATECONTROLMODELISTENER_H_
#define CLIMATECONTROLMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class ClimateControlModeListener : public ClimateControlModeIntfControlleeListener
{
  public:
    virtual QStatus OnSetMode(const uint16_t& mode);
    virtual QStatus OnGetMode(uint16_t& mode);
    virtual QStatus OnGetSupportedModes(SupportedModes& modes);
    virtual QStatus OnGetOperationalState(uint16_t& operationalState);
};

class ClimateControlModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    ClimateControlModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~ClimateControlModeCommands();

    virtual void Init();
    virtual void InitializeProperties();

    ClimateControlModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);
    static void OnCmdGetOperationalState(Commands* commands, std::string& cmd);
    static void OnCmdSetOperationalState(Commands* commands, std::string& cmd);

  private:
    ClimateControlModeIntfControllee* m_intfControllee;
    ClimateControlModeListener m_listener;
};

#endif /* CLIMATECONTROLMODELISTENER_H_ */