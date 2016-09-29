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

#ifndef TEMPERATUREDISPLAYCOMMANDS_H_
#define TEMPERATUREDISPLAYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class TemperatureDisplayListener : public TemperatureDisplayIntfControllerListener {
  public:
    TemperatureDisplayListener();
    virtual ~TemperatureDisplayListener();

    virtual void OnResponseGetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, const uint8_t temperatureUnit, void* context);

    virtual void OnResponseSetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, void* context);

    virtual void OnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& SupportedDisplayTemperatureUnits, void* context);

    virtual void OnDisplayTemperatureUnitChanged(const qcc::String& objectPath, const uint8_t temperatureUnit);

    virtual void OnSupportedDisplayTemperatureUnitsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& SupportedDisplayTemperatureUnits);

};

class TemperatureDisplayCommands : public InterfaceCommands
{
  public:
    TemperatureDisplayCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~TemperatureDisplayCommands();

    virtual void Init();

    TemperatureDisplayIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetDisplayTemperatureUnit(Commands* commands, std::string& cmd);
    static void OnCmdSetDisplayTemperatureUnit(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedDisplayTemperatureUnits(Commands* commands, std::string& cmd);

  private:
    TemperatureDisplayIntfController* m_intfController;
    TemperatureDisplayListener m_listener;
};


#endif /* TEMPERATUREDISPLAYCOMMANDS_H_ */
