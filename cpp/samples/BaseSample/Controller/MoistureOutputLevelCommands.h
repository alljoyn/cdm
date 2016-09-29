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

#ifndef MOISTUREOUTPUTLEVELCOMMANDS_H_
#define MOISTUREOUTPUTLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class MoistureOutputLevelListener : public MoistureOutputLevelIntfControllerListener {
  public:
    MoistureOutputLevelListener();
    virtual ~MoistureOutputLevelListener();

    virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const AutoMode autoMode);

    virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode autoMode, void* context);
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context);
};


class MoistureOutputLevelCommands : public InterfaceCommands
{
  public:
    MoistureOutputLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~MoistureOutputLevelCommands();

    virtual void Init();

    MoistureOutputLevelIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxMoistureOutputLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    MoistureOutputLevelIntfController* m_intfController;
    MoistureOutputLevelListener m_listener;
};

#endif /* MOISTUREOUTPUTLEVELCOMMANDS_H_ */
