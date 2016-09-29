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

#ifndef SOILLEVELCOMMANDS_H_
#define SOILLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class SoilLevelListener : public SoilLevelIntfControllerListener {
  public:
    SoilLevelListener();
    virtual ~SoilLevelListener();
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context);

    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context);

    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context);

    virtual void OnResponseGetSelectableLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context);

    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t maxLevel);

    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t targetLevel);

    virtual void OnSelectableLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels);

};

class SoilLevelCommands : public InterfaceCommands
{
  public:
    SoilLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~SoilLevelCommands();

    virtual void Init();

    SoilLevelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetSelectableLevels(Commands* commands, std::string& cmd);

  private:
    SoilLevelIntfController* m_intfController;
    SoilLevelListener m_listener;
};


#endif /* SOILLEVELCOMMANDS_H_ */
