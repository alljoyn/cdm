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

#ifndef RAPIDMODETIMEDCOMMANDS_H_
#define RAPIDMODETIMEDCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RapidModeTimedListener : public RapidModeTimedIntfControllerListener {
  public:
    RapidModeTimedListener();
    virtual ~RapidModeTimedListener();

    virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value);

    virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
    virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);
};

class RapidModeTimedCommands : public InterfaceCommands
{
  public:
    RapidModeTimedCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RapidModeTimedCommands();

    virtual void Init();

    RapidModeTimedIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdSetRapidModeMinutesRemaining(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxSetMinutes(Commands* commands, std::string& cmd);

  private:
    RapidModeTimedIntfController* m_intfController;
    RapidModeTimedListener m_listener;
};

#endif /* RAPIDMODETIMEDCOMMANDS_H_ */
