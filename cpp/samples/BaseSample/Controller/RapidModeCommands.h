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

#ifndef RAPIDMODECOMMANDS_H_
#define RAPIDMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RapidModeListener : public RapidModeIntfControllerListener{
  public:
    RapidModeListener();
    virtual ~RapidModeListener();
    virtual void RapidModePropertyChanged(const qcc::String& objectPath, const bool rapidMode);
    virtual void OnGetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, const bool rapidMode, void* context);
    virtual void OnSetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

};

class RapidModeCommands : public InterfaceCommands
{
  public:
    RapidModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RapidModeCommands();

    virtual void Init();

    RapidModeIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetRapidMode(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidMode(Commands* commands, std::string& cmd);

  private:
    RapidModeIntfController* m_intfController;
    RapidModeListener m_listener;
};


#endif /* RAPIDMODECOMMANDS_H_ */