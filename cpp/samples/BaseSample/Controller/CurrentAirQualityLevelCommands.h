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

#ifndef CURRENTAIRQUALITYLEVELCOMMANDS_H_
#define CURRENTAIRQUALITYLEVELCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentAirQualityLevelListener : public CurrentAirQualityLevelIntfControllerListener {
  public:
    CurrentAirQualityLevelListener();
    virtual ~CurrentAirQualityLevelListener();

    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context);
    virtual void OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value);
    virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const  uint8_t value);
};

class CurrentAirQualityLevelCommands : public InterfaceCommands
{
  public:
    CurrentAirQualityLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentAirQualityLevelCommands();

    virtual void Init();

    CurrentAirQualityLevelIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentLevel(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxLevel(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityLevelIntfController* m_intfController;
    CurrentAirQualityLevelListener m_listener;
};

#endif /* CURRENTAIRQUALITYLEVELCOMMANDS_H_ */
