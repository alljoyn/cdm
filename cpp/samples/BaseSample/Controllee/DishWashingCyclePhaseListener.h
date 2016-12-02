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

#ifndef DISHWASHINGCYCLEPHASELISTENER_H_
#define DISHWASHINGCYCLEPHASELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControlleeListener.h>

using namespace ajn;
using namespace services;


class DishWashingCyclePhaseListener : public DishWashingCyclePhaseIntfControlleeListener
{
public:
        virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase);

        virtual QStatus OnGetSupportedCyclePhases(DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases);

        virtual QStatus OnGetCyclePhasesDescriptions(const qcc::String& language,
                                                     DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfPhasesDescs,
                                                     ErrorCode& errorCode);

};

class DishWashingCyclePhaseCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    DishWashingCyclePhaseCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~DishWashingCyclePhaseCommands();

    virtual void Init();
    virtual void InitializeProperties();

    DishWashingCyclePhaseIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);
    static void OnCmdSetCyclePhase(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);
//    static void OnCmdSetSupportedCyclePhases(Commands* commands, std::string& cmd);

  private:
    DishWashingCyclePhaseIntfControllee* m_intfControllee;
    DishWashingCyclePhaseListener m_listener;
};

#endif /* DISHWASHINGCYCLEPHASELISTENER_H_ */