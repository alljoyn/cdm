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

#ifndef CURRENTAIRQUALITYLISTENER_H_
#define CURRENTAIRQUALITYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentAirQualityListener : public CurrentAirQualityIntfControlleeListener
{
  public:
    virtual QStatus OnGetContaminantType(uint8_t& type);
    virtual QStatus OnGetCurrentValue(double& value);
    virtual QStatus OnGetMaxValue(double& value);
    virtual QStatus OnGetMinValue(double& value);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
};

class CurrentAirQualityCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    CurrentAirQualityCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~CurrentAirQualityCommands();

    virtual void Init();
    virtual void InitializeProperties();

    CurrentAirQualityIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdSetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdSetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdSetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);
    static void OnCmdSetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityIntfControllee* m_intfControllee;
    CurrentAirQualityListener m_listener;
};



#endif /* CURRENTAIRQAULITYLISTENER_H_ */
