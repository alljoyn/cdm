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

#ifndef CYCLECONTROLCOMMANDS_H_
#define CYCLECONTROLCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CycleControlListener : public CycleControlIntfControllerListener{
  public:
    CycleControlListener();
    virtual ~CycleControlListener();
    virtual void GetOperationalStatePropertyCallback(QStatus status, const qcc::String& objectPath, const CycleControlInterface::OperationalState& state, void* context);

    virtual void GetSupportedStatesPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states, void* context);

    virtual void GetSupportedCommandsPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands, void* context);

    virtual void OperationalStatePropertyChanged(const qcc::String& objectPath, const CycleControlInterface::OperationalState& state);

    virtual void SupportedOperationalStatesProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states);

    virtual void SupportedOperationalCommandsProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands);

    virtual void OnExecuteCommandRespose(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage);
};

class CycleControlCommands : public InterfaceCommands
{
  public:
    CycleControlCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CycleControlCommands();

    virtual void Init();

    CycleControlIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetOperationalState(Commands* commands, std::string& cmd);

    static void OnCmdExecuteCommand(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedOperationalCommands(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedOperationalStates(Commands* commands, std::string& cmd);
  private:
    CycleControlIntfController* m_intfController;
    CycleControlListener m_listener;
};


#endif /* CYCLECONTROLCOMMANDS_H_ */
