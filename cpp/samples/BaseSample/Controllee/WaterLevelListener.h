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

#ifndef WATERLEVELLISTENER_H_
#define WATERLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class WaterLevelListener : public WaterLevelIntfControlleeListener
{
  public:
        virtual QStatus OnGetCurrentLevel(uint8_t& currentLevel);

        virtual QStatus OnGetMaxLevel(uint8_t& maxLevel);

        virtual QStatus OnGetSupplySource(WaterLevelInterface::WaterLevelSupplySource& supplySource);
};

class WaterLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    WaterLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~WaterLevelCommands();

    virtual void Init();
    virtual void InitializeProperties();

    WaterLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxLevel(Commands* commands, std::string& cmd);

    static void OnCmdGetSupplySource(Commands* commands, std::string& cmd);
    static void OnCmdSetSupplySource(Commands* commands, std::string& cmd);

  private:
    WaterLevelIntfControllee* m_intfControllee;
    WaterLevelListener m_listener;
};

#endif /* WATERLEVELLISTENER_H_ */
