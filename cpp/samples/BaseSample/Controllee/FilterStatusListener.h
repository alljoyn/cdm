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

#ifndef FILTERSTATUSLISTENER_H_
#define FILTERSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class FilterStatusListener : public FilterStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetExpectedLifeInDays(uint16_t& value);
    virtual QStatus OnGetIsCleanable(bool& isCleanable);
    virtual QStatus OnGetOrderPercentage(uint8_t& value);
    virtual QStatus OnGetManufacturer(qcc::String& manufacturer);
    virtual QStatus OnGetPartNumber(qcc::String& partNumber);
    virtual QStatus OnGetUrl(qcc::String& url);
    virtual QStatus OnGetLifeRemaining(uint8_t& value);
};

class FilterStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    FilterStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~FilterStatusCommands();

    virtual void Init();
    virtual void InitializeProperties();

    FilterStatusIntfControllee* GetInterface() { return m_intfControllee; }

    static void OnCmdGetExpectedLifeInDays(Commands* commands, std::string& cmd);
    static void OnCmdSetExpectedLifeInDays(Commands* commands, std::string& cmd);
    static void OnCmdGetIsCleanable(Commands* commands, std::string& cmd);
    static void OnCmdSetIsCleanable(Commands* commands, std::string& cmd);
    static void OnCmdGetOrderPercentage(Commands* commands, std::string& cmd);
    static void OnCmdSetOrderPercentage(Commands* commands, std::string& cmd);
    static void OnCmdGetManufacturer(Commands* commands, std::string& cmd);
    static void OnCmdGetPartNumber(Commands* commands, std::string& cmd);
    static void OnCmdGetUrl(Commands* commands, std::string& cmd);
    static void OnCmdGetLifeRemaining(Commands* commands, std::string& cmd);
    static void OnCmdSetLifeRemaining(Commands* commands, std::string& cmd);

  private:
    FilterStatusIntfControllee* m_intfControllee;
    FilterStatusListener m_listener;
};

#endif /* FILTERSTATUSLISTENER_H_ */