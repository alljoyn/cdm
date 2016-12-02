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

#ifndef LAUNDRYCYCLEPHASEINTFCONTROLLER_H_
#define LAUNDRYCYCLEPHASEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * LaundryCyclePhase Interface Controller class
 */
class LaundryCyclePhaseIntfController : public LaundryCyclePhaseInterface {
  public:
    /**
     * Constructor of LaundryCyclePhaseIntfController
     */
    LaundryCyclePhaseIntfController() {}

    /**
     * Destructor of LaundryCyclePhaseIntfController
     */
    virtual ~LaundryCyclePhaseIntfController() {}

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

#endif /* LAUNDRYCYCLEPHASEINTFCONTROLLER_H_ */