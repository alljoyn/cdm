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

#ifndef HVACFANMODELISTENER_H_
#define HVACFANMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class HvacFanModeListener : public HvacFanModeIntfControlleeListener
{
  public:
    virtual QStatus OnSetMode(const uint16_t& mode);
    virtual QStatus OnGetMode(uint16_t& mode);
    virtual QStatus OnGetSupportedModes(SupportedModes& modes);
};

class HvacFanModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    HvacFanModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~HvacFanModeCommands();

    virtual void Init();
    virtual void InitializeProperties();

    HvacFanModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetMode(Commands* commands, std::string& cmd);
    static void OnCmdSetMode(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedModes(Commands* commands, std::string& cmd);

  private:
    HvacFanModeIntfControllee* m_intfControllee;
    HvacFanModeListener m_listener;
};

#endif /* HVACFANMODELISTENER_H_ */
