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

#ifndef OFFCONTROLCOMMANDS_H_
#define OFFCONTROLCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OffControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class OffControlListener : public OffControlIntfControllerListener {
  public:
    OffControlListener();
    virtual ~OffControlListener();
    virtual void OnSwitchOff(QStatus status, const qcc::String& objectPath, void* context,
                                         const char* errorName, const char* errorMessage);
};

class OffControlCommands : public InterfaceCommands
{
  public:
    OffControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~OffControlCommands();

    virtual void Init();

    OffControlIntfController* GetInterface() { return m_intfController; }

    static void OffCmdSwitchOff(Commands* commands, std::string& cmd);

  private:
    OffControlIntfController* m_intfController;
    OffControlListener m_listener;
};

#endif /* OFFCONTROLCOMMANDS_H_ */
