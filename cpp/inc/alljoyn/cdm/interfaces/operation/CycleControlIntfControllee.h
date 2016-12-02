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

#ifndef CYCLECONTROLINTFCONTROLLEE_H_
#define CYCLECONTROLINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {


/**
 * CycleControl Interface Controllee class
 */
class CycleControlIntfControllee : public CycleControlInterface {
  public:
    /**
     * Constructor of CycleControlIntfControllee
     */
    CycleControlIntfControllee() {}

    /**
     * Destructor of CycleControlIntfControllee
     */
    virtual ~CycleControlIntfControllee() {}

    /**
     * Get OpertaionalState
     * @return OpertaionalState
     */
    virtual const CycleControlOperationalState GetOperationalState() const = 0 ;

    /**
     * Set OperationalState
     * @param[in]  state the state to set
     * @return ER_OK on success
     */
    virtual QStatus SetOperationalState(CycleControlOperationalState state) = 0;

    /**
     * Get SupportedCommands
     * @return The list of supported commands
     */
    virtual const SupportedOperationalCommands& GetSupportedCommands() const = 0;

    /**
     * Get SupportedStates
     * @return The list of supported states
     */
    virtual const SupportedOperationalStates& GetSupportedStates() const = 0;
    /**
     * Set SupportedCommands
     * @param[in]  commands the list of commands to set
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedCommands(SupportedOperationalCommands commands) = 0;

    /**
     * Set SupportedStates
     * @param[in]  states the list of states to set
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedStates(SupportedOperationalStates states) = 0;

};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLEE_H_ */