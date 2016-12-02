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

#ifndef LAUNDRYCYCLEPHASELISTENER_H_
#define LAUNDRYCYCLEPHASELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfControlleeListener.h>

using namespace ajn;
using namespace services;


class LaundryCyclePhaseListener : public LaundryCyclePhaseIntfControlleeListener
{
public:
        virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase);

        virtual QStatus OnGetSupportedCyclePhases(LaundryCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases);

        virtual QStatus OnGetCyclePhasesDescriptions(const qcc::String& language,
                                                     LaundryCyclePhaseInterface::CyclePhaseDescriptions& listOfPhasesDescs,
                                                     ErrorCode& errorCode);

};

class LaundryCyclePhaseCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    LaundryCyclePhaseCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~LaundryCyclePhaseCommands();

    virtual void Init();
    virtual void InitializeProperties();

    LaundryCyclePhaseIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);
    static void OnCmdSetCyclePhase(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);
//    static void OnCmdSetSupportedCyclePhases(Commands* commands, std::string& cmd);

  private:
    LaundryCyclePhaseIntfControllee* m_intfControllee;
    LaundryCyclePhaseListener m_listener;
};

#endif /* LAUNDRYCYCLEPHASELISTENER_H_ */