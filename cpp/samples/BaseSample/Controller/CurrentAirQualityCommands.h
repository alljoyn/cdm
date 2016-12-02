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

#ifndef CURRENTAIRQUALITYCOMMANDS_H_
#define CURRENTAIRQUALITYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentAirQualityListener : public CurrentAirQualityIntfControllerListener {
  public:
    CurrentAirQualityListener();
    virtual ~CurrentAirQualityListener();

    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context);
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);

    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value);
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const  double value);
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value);
};

class CurrentAirQualityCommands : public InterfaceCommands
{
  public:
    CurrentAirQualityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentAirQualityCommands();

    virtual void Init();

    CurrentAirQualityIntfController* GetInterface() { return m_intfController.get(); }

    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityIntfControllerPtr m_intfController;
    CurrentAirQualityListener m_listener;
};

#endif /* CURRENTAIRQUALITYCOMMANDS_H_ */
