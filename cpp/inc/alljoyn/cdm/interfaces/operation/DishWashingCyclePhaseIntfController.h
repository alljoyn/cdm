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

#ifndef DISHWASHINGCYCLEPHASEINTFCONTROLLER_H_
#define DISHWASHINGCYCLEPHASEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface Controller class
 */
class DishWashingCyclePhaseIntfController : public DishWashingCyclePhaseInterface {
  public:
    /**
     * Constructor of DishWashingCyclePhaseIntfController
     */
    DishWashingCyclePhaseIntfController() {}

    /**
     * Destructor of DishWashingCyclePhaseIntfController
     */
    virtual ~DishWashingCyclePhaseIntfController() {}

    /**
     * Get CyclePhase
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCyclePhase(void* context = NULL) = 0;

    /**
     * Get SupportedCyclePhases
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedCyclePhases(void* context = NULL) = 0;

    /**
     * Get CyclePhasesDescriptions
     * @param[in] language language
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCyclePhasesDescriptions(const qcc::String& language, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTFCONTROLLER_H_ */