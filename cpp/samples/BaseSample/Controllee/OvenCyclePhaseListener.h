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

#ifndef OVENCYCLEPHASELISTENER_H_
#define OVENCYCLEPHASELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OvenCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OvenCyclePhaseIntfControlleeListener.h>

using namespace ajn;
using namespace services;


class OvenCyclePhaseListener : public OvenCyclePhaseIntfControlleeListener
{
public:
        virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase);

        virtual QStatus OnGetSupportedCyclePhases(OvenCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases);

        virtual QStatus OnGetCyclePhasesDescriptions(const qcc::String& language,
                                                     OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfPhasesDescs,
                                                     ErrorCode& errorCode);

};
class OvenCyclePhaseCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OvenCyclePhaseCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OvenCyclePhaseCommands();

    virtual void Init();
    virtual void InitializeProperties();

    OvenCyclePhaseIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetCyclePhase(Commands* commands, std::string& cmd);
    static void OnCmdSetCyclePhase(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd);
//    static void OnCmdSetSupportedCyclePhases(Commands* commands, std::string& cmd);

  private:
    OvenCyclePhaseIntfControllee* m_intfControllee;
    OvenCyclePhaseListener m_listener;
};

#endif /* OVENCYCLEPHASELISTENER_H_ */