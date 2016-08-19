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

#ifndef TARGETTEMPERATURELISTENER_H_
#define TARGETTEMPERATURELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TargetTemperatureListener : public TargetTemperatureIntfControlleeListener
{
  public:
    virtual QStatus OnSetTargetValue(const double value);
    virtual QStatus OnGetTargetValue(double& value);
    virtual QStatus OnGetMinValue(double& value);
    virtual QStatus OnGetMaxValue(double& value);
    virtual QStatus OnGetStepValue(double& value);
};

class TargetTemperatureCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TargetTemperatureCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TargetTemperatureCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TargetTemperatureIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdSetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);
    static void OnCmdSetStepValue(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureIntfControllee* m_intfControllee;
    TargetTemperatureListener m_listener;
};



#endif /* TARGETTEMPERATURELISTENER_H_ */
