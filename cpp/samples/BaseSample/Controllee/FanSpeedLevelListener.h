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

#ifndef FANSPEEDLEVELLISTENER_H_
#define FANSPEEDLEVELLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class FanSpeedLevelListener : public FanSpeedLevelIntfControlleeListener
{
  public:
    virtual QStatus OnSetFanSpeedLevel(const uint8_t& value);
    virtual QStatus OnGetFanSpeedLevel(uint8_t& value);
    virtual QStatus OnGetMaxFanSpeedLevel(uint8_t& value);
    virtual QStatus OnSetAutoMode(const uint8_t& value);
    virtual QStatus OnGetAutoMode(uint8_t& value);
};

class FanSpeedLevelCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    FanSpeedLevelCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~FanSpeedLevelCommands();

    virtual void Init();

    FanSpeedLevelIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxFanSpeedLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetAutoMode(Commands* commands, std::string& cmd);

  private:
    FanSpeedLevelIntfControllee* m_intfControllee;
    FanSpeedLevelListener m_listener;
};

#endif /* FANSPEEDLEVELLISTENER_H_ */
