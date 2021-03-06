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

#ifndef BATTERYSTATUSLISTENER_H_
#define BATTERYSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class BatteryStatusListener : public BatteryStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetCurrentValue(uint8_t& currentValue);
    virtual QStatus OnGetIsCharging(bool& isCharging);

};

class BatteryStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    BatteryStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~BatteryStatusCommands();

    virtual void Init();

    BatteryStatusIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetIsCharging(Commands* commands, std::string& cmd);
    static void OnCmdSetIsCharging(Commands* commands, std::string& cmd);

  private:
    BatteryStatusIntfControllee* m_intfControllee;
    BatteryStatusListener m_listener;
};

#endif /* BATTERYSTATUSLISTENER_H_ */
