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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLER_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface Controller class
 */
class RobotCleaningCyclePhaseIntfController : public RobotCleaningCyclePhaseInterface {
  public:
    /**
     * Constructor of RobotCleaningCyclePhaseIntfController
     */
    RobotCleaningCyclePhaseIntfController() {}

    /**
     * Destructor of RobotCleaningCyclePhaseIntfController
     */
    virtual ~RobotCleaningCyclePhaseIntfController() {}

    /**
     * Get cycle phase
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCyclePhase(void* context = NULL) = 0;

    /**
     * Get supported cycle phases
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedCyclePhases(void* context = NULL) = 0;

    /**
     * Get vendor phases description
     * @param[in] languageTag language tag
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLER_H_ */