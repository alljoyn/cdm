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

#ifndef SPINSPEEDLEVELCOMMANDS_H_
#define SPINSPEEDLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/SpinSpeedLevelIntfController.h>
#include <alljoyn/hae/interfaces/operation/SpinSpeedLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class SpinSpeedLevelListener : public SpinSpeedLevelIntfControllerListener{
  public:
    SpinSpeedLevelListener();
    virtual ~SpinSpeedLevelListener();
    virtual void GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context);

    virtual void GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context);

    virtual void SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context);

    virtual void GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context);

    virtual void MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel);

    virtual void TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel);

    virtual void SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels);

};

class SpinSpeedLevelCommands : public InterfaceCommands
{
  public:
    SpinSpeedLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~SpinSpeedLevelCommands();

    virtual void Init();

    SpinSpeedLevelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableLevels(Commands* commands, std::string& cmd);

  private:
    SpinSpeedLevelIntfController* m_intfController;
    SpinSpeedLevelListener m_listener;
};


#endif /* SPINSPEEDLEVELCOMMANDS_H_ */
