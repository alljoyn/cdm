/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef HVACFANMODECOMMANDS_H_
#define HVACFANMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class HvacFanModeListener : public HvacFanModeIntfControllerListener {
  public:
    HvacFanModeListener();
    virtual ~HvacFanModeListener();

    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context);
    virtual void OnModeChanged(const qcc::String& objectPath, const uint16_t value);
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value);
};


class HvacFanModeCommands : public InterfaceCommands
{
  public:
    HvacFanModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~HvacFanModeCommands();

    virtual void Init();

    HvacFanModeIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);

  private:
    HvacFanModeIntfController* m_intfController;
    HvacFanModeListener m_listener;
};

#endif /* HVACFANMODECOMMANDS_H_ */
