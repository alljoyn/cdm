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

#ifndef ONCONTROLCOMMANDS_H_
#define ONCONTROLCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/OnControlIntfController.h>
#include <alljoyn/hae/interfaces/operation/OnControlIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class OnControlListener : public OnControlIntfControllerListener {
  public:
    OnControlListener();
    virtual ~OnControlListener();
    virtual void OnSwitchOn(QStatus status, const qcc::String& objectPath, void* context,
                                         const char* errorName, const char* errorMessage);
};

class OnControlCommands : public InterfaceCommands
{
  public:
    OnControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~OnControlCommands();

    virtual void Init();

    OnControlIntfController* GetInterface() { return m_intfController; }

    static void OnCmdSwitchOn(Commands* commands, std::string& cmd);

  private:
    OnControlIntfController* m_intfController;
    OnControlListener m_listener;
};

#endif /* ONCONTROLCOMMANDS_H_ */
