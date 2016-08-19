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

#ifndef CURRENTTEMPERATURELISTENER_H_
#define CURRENTTEMPERATURELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentTemperatureListener : public CurrentTemperatureIntfControlleeListener
{
  public:
    virtual QStatus OnGetCurrentValue(double& value);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
};

class CurrentTemperatureCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentTemperatureCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentTemperatureCommands();

    virtual void Init();

    CurrentTemperatureIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdSetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentTemperatureIntfControllee* m_intfControllee;
    CurrentTemperatureListener m_listener;
};

#endif /* CURRENTTEMPERATURELISTENER_H_ */
