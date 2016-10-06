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

#ifndef LANGUAGEDISPLAYCOMMANDS_H_
#define LANGUAGEDISPLAYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class LanguageDisplayListener : public LanguageDisplayIntfControllerListener {
  public:
    LanguageDisplayListener();
    virtual ~LanguageDisplayListener();

    virtual void GetDisplayLanguagePropertyCallback(QStatus status, const qcc::String& objectPath, const qcc::String displayLanguage, void* context);

    virtual void SetDisplayLanguagePropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

    virtual void GetSupportedDisplayLanguagesPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages, void* context);

    virtual void DisplayLanguagePropertyChanged(const qcc::String& objectPath, const qcc::String displayLanguage);

    virtual void SupportedDisplayLanguagesPropertyChanged(const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages);

};

class LanguageDisplayCommands : public InterfaceCommands
{
  public:
    LanguageDisplayCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~LanguageDisplayCommands();

    virtual void Init();

    LanguageDisplayIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetDisplayLanguage(Commands* commands, std::string& cmd);
    static void OnCmdSetDisplayLanguage(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedDisplayLanguages(Commands* commands, std::string& cmd);

  private:
    LanguageDisplayIntfController* m_intfController;
    LanguageDisplayListener m_listener;
};


#endif /* LANGUAGEDISPLAYCOMMANDS_H_ */