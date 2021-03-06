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

#ifndef REMOTECONTROLLABILITYCOMMANDS_H_
#define REMOTECONTROLLABILITYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RemoteControllabilityListener : public RemoteControllabilityIntfControllerListener{
  public:
    RemoteControllabilityListener();
    virtual ~RemoteControllabilityListener();
    virtual void IsControllablePropertyChanged(const qcc::String& objectPath, const bool isControllable);
    virtual void GetIsControllablePropertyCallback(QStatus status, const qcc::String& objectPath, const bool isControllable, void* context);
};

class RemoteControllabilityCommands : public InterfaceCommands
{
  public:
    RemoteControllabilityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RemoteControllabilityCommands();

    virtual void Init();

    RemoteControllabilityIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetIsControllable(Commands* commands, std::string& cmd);
    //static void OnCmdSetIsClosed(Commands* commands, std::string& cmd);

  private:
    RemoteControllabilityIntfController* m_intfController;
    RemoteControllabilityListener m_listener;
};


#endif /* REMOTECONTROLLABILITYCOMMANDS_H_ */
