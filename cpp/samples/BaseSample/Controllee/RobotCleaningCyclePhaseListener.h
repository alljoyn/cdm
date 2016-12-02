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

#ifndef ROBOTCLEANINGCYCLEPHASELISTENER_H_
#define ROBOTCLEANINGCYCLEPHASELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class RobotCleaningCyclePhaseListener : public RobotCleaningCyclePhaseIntfControlleeListener
{
  public:
    virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase);
    virtual QStatus OnGetSupportedCyclePhases(RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases);
    virtual QStatus OnGetVendorPhasesDescription(const qcc::String& languageTag,
                                                 RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                 ErrorCode& errorCode);
};

//////////////////////////////////////////////////////////////////////////////////////////////
class RobotCleaningCyclePhaseCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RobotCleaningCyclePhaseCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RobotCleaningCyclePhaseCommands();

    virtual void Init();
    virtual void InitializeProperties();

    RobotCleaningCyclePhaseIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);
    static void OnCmdSetCyclePhase(Commands* commands, std::string& cmd);
    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);

  private:
    RobotCleaningCyclePhaseIntfControllee* m_intfControllee;
    RobotCleaningCyclePhaseListener m_listener;
};



#endif /* ROBOTCLEANINGCYCLEPHASELISTENER_H_ */