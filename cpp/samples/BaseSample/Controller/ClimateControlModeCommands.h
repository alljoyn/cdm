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

#ifndef CLIMATECONTROLMODECOMMANDS_H_
#define CLIMATECONTROLMODECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class ClimateControlModeListener : public ClimateControlModeIntfControllerListener {
  public:
    ClimateControlModeListener();
    virtual ~ClimateControlModeListener();

    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context);
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context);
    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context);
    virtual void OnModeChanged(const qcc::String& objectPath, const Mode value);
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value);
    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value);
};


class ClimateControlModeCommands : public InterfaceCommands
{
  public:
    ClimateControlModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~ClimateControlModeCommands();

    virtual void Init();

    ClimateControlModeIntfController* GetInterface() { return m_intfController.get(); }

    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);
    static void OnCmdGetOperationalState(Commands* commands, std::string& cmd);

  private:
    ClimateControlModeIntfControllerPtr m_intfController;
    ClimateControlModeListener m_listener;
};

#endif /* CLIMATECONTROLMODECOMMANDS_H_ */
