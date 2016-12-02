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

#ifndef CYCLECONTROLINTFCONTROLLER_H_
#define CYCLECONTROLINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controller class
 */
class CycleControlIntfController : public CycleControlInterface {
  public:
    /**
     * Constructor of CycleControlIntfController
     */
    CycleControlIntfController() {}

    /**
     * Destructor of CycleControlIntfController
     */
    virtual ~CycleControlIntfController() {}

    /**
     * Get OperationalState
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOperationalState(void* context = NULL) = 0;

    /**
     * Get SupportedOperationalCommands
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedOperationalCommands(void* context = NULL) = 0;

    /**
     * Get SupportedOperationalStates
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedOperationalStates(void* context = NULL) = 0;

    /**
     * Execute command
     * @param[in] command command to execude
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus ExecuteCommand(const CycleControlOperationalCommand command, void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLER_H_ */