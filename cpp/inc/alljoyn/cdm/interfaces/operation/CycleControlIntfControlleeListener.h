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

#ifndef CYCLECONTROLINTFCONTROLLEELISTENER_H_
#define CYCLECONTROLINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controllee Listener class
 */
class CycleControlIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of CycleControlIntfControlleeListener
     */
    virtual ~CycleControlIntfControlleeListener() {}

    /**
     * Handler for getting current operational state
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] currentState currentState
     * @return ER_OK on success
     */
    virtual QStatus OnGetOperationalState(CycleControlInterface::CycleControlOperationalState& currentState) = 0;

    /**
     * Handler for executing command
     * @param[in] command command to execute
     * @param[out] currentState currentState
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus OnExecuteCommand(CycleControlInterface::CycleControlOperationalCommand command, CycleControlInterface::CycleControlOperationalState& newState, ErrorCode& error) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLEELISTENER_H_ */