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

#ifndef ROBOTCLEANINGCYCLEPHASECOMMANDS_H_
#define ROBOTCLEANINGCYCLEPHASECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/RobotCleaningCyclePhaseIntfController.h>
#include <alljoyn/hae/interfaces/operation/RobotCleaningCyclePhaseIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class RobotCleaningCyclePhaseListener : public RobotCleaningCyclePhaseIntfControllerListener {
  public:
    RobotCleaningCyclePhaseListener();
    virtual ~RobotCleaningCyclePhaseListener();
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t cyclePhase, void* context);
    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath,
                                                   const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases, void* context);
    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath,
                                                      const RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                      void* context, const char* errorName, const char* errorMessage);
    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase);
    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases);
};

class RobotCleaningCyclePhaseCommands : public InterfaceCommands
{
  public:
    RobotCleaningCyclePhaseCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~RobotCleaningCyclePhaseCommands();

    virtual void Init();

    RobotCleaningCyclePhaseIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);
    static void OnCmdGetVendorPhasesDescription(Commands* commands, std::string& cmd);

  private:
    RobotCleaningCyclePhaseIntfController* m_intfController;
    RobotCleaningCyclePhaseListener m_listener;
};

#endif /* ROBOTCLEANINGCYCLEPHASECOMMANDS_H_ */
