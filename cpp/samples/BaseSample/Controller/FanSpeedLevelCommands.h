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

#ifndef FANSPEEDLEVELCOMMANDS_H_
#define FANSPEEDLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class FanSpeedLevelListener : public FanSpeedLevelIntfControllerListener {
  public:
    FanSpeedLevelListener();
    virtual ~FanSpeedLevelListener();

    virtual void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context);
    virtual void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const AutoMode value);
};


class FanSpeedLevelCommands : public InterfaceCommands
{
  public:
    FanSpeedLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~FanSpeedLevelCommands();

    virtual void Init();

    FanSpeedLevelIntfController* GetInterface() { return m_intfController.get(); }

    static void OnCmdGetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    FanSpeedLevelIntfControllerPtr m_intfController;
    FanSpeedLevelListener m_listener;
};

#endif /* FANSPEEDLEVELCOMMANDS_H_ */
