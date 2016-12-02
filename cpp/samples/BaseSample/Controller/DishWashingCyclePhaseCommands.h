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
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context);

    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context);

    virtual void OnCyclePhasePropertyChanged(const qcc::String& objectPath, const uint8_t cyclePhase);

    virtual void OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases listOfCyclePhases);

    virtual void OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions, void* context, const char* errorName, const char* errorMessage);
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