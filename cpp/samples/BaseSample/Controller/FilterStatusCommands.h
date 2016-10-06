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

#ifndef FILTERSTATUSCOMMANDS_H_
#define FILTERSTATUSCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllerListener.h>

class FilterStatusListener : public FilterStatusIntfControllerListener {
  public:
    FilterStatusListener();
    virtual ~FilterStatusListener();

    virtual void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnIsCleanableChanged(const qcc::String& objectPath, const bool isCleanable);
    virtual void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value);

    virtual void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool isCleanable, void* context);
    virtual void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& manufacturer, void* context);
    virtual void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& partNumber, void* context);
    virtual void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& url, void* context);
    virtual void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
};


class FilterStatusCommands : public InterfaceCommands
{
  public:
    FilterStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~FilterStatusCommands();

    virtual void Init();

    FilterStatusIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetExpectedLifeInDays(Commands* commands, std::string& cmd);
    static void OnCmdGetIsCleanable(Commands* commands, std::string& cmd);
    static void OnCmdGetOrderPercentage(Commands* commands, std::string& cmd);
    static void OnCmdGetManufacturer(Commands* commands, std::string& cmd);
    static void OnCmdGetPartNumber(Commands* commands, std::string& cmd);
    static void OnCmdGetUrl(Commands* commands, std::string& cmd);
    static void OnCmdGetLifeRemaining(Commands* commands, std::string& cmd);

  private:
    FilterStatusIntfController* m_intfController;
    FilterStatusListener m_listener;
};

#endif /* FILTERSTATUSCOMMANDS_H_ */