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

#ifndef DISHWASHINGCYCLEPHASECOMMANDS_H_
#define DISHWASHINGCYCLEPHASECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfController.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class DishWashingCyclePhaseListener : public DishWashingCyclePhaseIntfControllerListener{
  public:
    DishWashingCyclePhaseListener();
    virtual ~DishWashingCyclePhaseListener();
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t cyclePhase, void* context);

    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context);

    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase);

    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases);

    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions, void* context, const char* errorName, const char* errorMessage);
};

class DishWashingCyclePhaseCommands : public InterfaceCommands
{
  public:
        DishWashingCyclePhaseCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~DishWashingCyclePhaseCommands();

    virtual void Init();

    DishWashingCyclePhaseIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);

    static void OnCmdGetCyclePhasesDescriptions(Commands* commands, std::string& cmd);
  private:
    DishWashingCyclePhaseIntfController* m_intfController;
    DishWashingCyclePhaseListener m_listener;
};


#endif /* DISHWASHINGCYCLEPHASECOMMANDS_H_ */
