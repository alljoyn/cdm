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

#ifndef VENDORDEFINEDCOMMANDS_H_
#define VENDORDEFINEDCOMMANDS_H_

#include "InterfaceCommands.h"
#include "VendorDefinedIntfController.h"
#include "VendorDefinedIntfControllerListener.h"

class ControllerSample;

using namespace ajn;
using namespace services;

class VendorDefinedListener : public VendorDefinedIntfControllerListener {
  public:
    VendorDefinedListener();
    virtual ~VendorDefinedListener();
    virtual void OnResponseSetTestProperty(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTestProperty(QStatus status, const qcc::String& objectPath, int32_t property, void* context);
    virtual void OnResponseTestMethod(QStatus status, const qcc::String& objectPath,
            void* context, const char* errorName, const char* errorMessage);

    /*
     * TODO: define functions that receives the PropertyChanged and other signals
     */
    virtual void OnTestPropertyChanged(const qcc::String& objectPath, const int32_t property);
    virtual void OnTestSignal(const qcc::String& objectPath);
};

class VendorDefinedCommands : public InterfaceCommands
{
  public:
    VendorDefinedCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~VendorDefinedCommands();

    virtual void Init();

    VendorDefinedIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetTestProperty(Commands* commands, std::string& cmd);
    static void OnCmdSetTestProperty(Commands* commands, std::string& cmd);
    static void OnCmdTestMethod(Commands* commands, std::string& cmd);

  private:
    VendorDefinedIntfController* m_intfController;
    VendorDefinedListener m_listener;
};

#endif /* VENDORDEFINEDCOMMANDS_H_ */