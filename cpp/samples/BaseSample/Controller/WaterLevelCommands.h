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

#ifndef WATERLEVELCOMMANDS_H_
#define WATERLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfController.h>
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class WaterLevelListener : public WaterLevelIntfControllerListener{
  public:
    WaterLevelListener();
    virtual ~WaterLevelListener();
    virtual void OnGetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnGetSupplySourcePropertyCallback (QStatus status, const qcc::String& objectPath, const WaterLevelInterface::WaterLevelSupplySource value, void* context);
    virtual void OnGetCurrentLevelPropertyCallback (QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);

    virtual void MaxLevelProprtyChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void CurrentLevelProprtyChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void SupplySourceProprtyChanged(const qcc::String& objectPath, const WaterLevelInterface::WaterLevelSupplySource value);
};

class WaterLevelCommands : public InterfaceCommands
{
  public:
    WaterLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~WaterLevelCommands();

    virtual void Init();

    WaterLevelIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetSupplySource(Commands* commands, std::string& cmd);

  private:
    WaterLevelIntfController* m_intfController;
    WaterLevelListener m_listener;
};


#endif /* WATERLEVELCOMMANDS_H_ */
