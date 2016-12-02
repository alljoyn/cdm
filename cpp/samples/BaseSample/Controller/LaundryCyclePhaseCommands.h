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

#ifndef LAUNDRYCYCLEPHASECOMMANDS_H_
#define LAUNDRYCYCLEPHASECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfController.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class LaundryCyclePhaseListener : public LaundryCyclePhaseIntfControllerListener{
  public:
    LaundryCyclePhaseListener();
    virtual ~LaundryCyclePhaseListener();
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context);

    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const LaundryCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context);

    virtual void OnCyclePhasePropertyChanged(const qcc::String& objectPath, const uint8_t cyclePhase);

    virtual void OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const LaundryCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases);

    virtual void OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const LaundryCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions, void* context, const char* errorName, const char* errorMessage);
};

class LaundryCyclePhaseCommands : public InterfaceCommands
{
  public:
        LaundryCyclePhaseCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~LaundryCyclePhaseCommands();

    virtual void Init();

    LaundryCyclePhaseIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);

    static void OnCmdGetCyclePhasesDescriptions(Commands* commands, std::string& cmd);
  private:
    LaundryCyclePhaseIntfController* m_intfController;
    LaundryCyclePhaseListener m_listener;
};


#endif /* LAUNDRYCYCLEPHASECOMMANDS_H_ */