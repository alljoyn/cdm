/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef ROBOTCLEANINGCYCLEPHASECOMMANDS_H_
#define ROBOTCLEANINGCYCLEPHASECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllerListener.h>

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