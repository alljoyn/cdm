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

#ifndef TESTCYCLECONTROLLISTENER_H_
#define TESTCYCLECONTROLLISTENER_H_

#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControlleeListener.h>

using namespace ajn;
using namespace services;
class TestCycleControlListener : public CycleControlIntfControlleeListener
{
private:
    void * m_testControllee;

public:
    TestCycleControlListener(void * controllee);

    virtual QStatus OnGetOperationalState(CycleControlInterface::CycleControlOperationalState& state);

    virtual QStatus OnExecuteCommand(CycleControlInterface::CycleControlOperationalCommand command, CycleControlInterface::CycleControlOperationalState& newState, ErrorCode& error);

};

#endif /* TESTCYCLECONTROLLISTENER_H_ */