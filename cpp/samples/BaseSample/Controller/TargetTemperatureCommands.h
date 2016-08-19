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

#ifndef TARGETTEMPERATURECOMMANDS_H_
#define TARGETTEMPERATURECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TargetTemperatureListener : public TargetTemperatureIntfControllerListener {
  public:
    TargetTemperatureListener();
    virtual ~TargetTemperatureListener();

    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context);

    virtual void OnTargetValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const  double value);
    virtual void OnStepValueChanged(const qcc::String& objectPath, const double value);

};

class TargetTemperatureCommands : public InterfaceCommands
{
  public:
    TargetTemperatureCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TargetTemperatureCommands();

    virtual void Init();

    TargetTemperatureIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetTargetValue(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetValue(Commands* commands, std::string& cmd);

    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetStepValue(Commands* commands, std::string& cmd);

  private:
    TargetTemperatureIntfController* m_intfController;
    TargetTemperatureListener m_listener;
};

#endif /* TARGETTEMPERATURECOMMANDS_H_ */
