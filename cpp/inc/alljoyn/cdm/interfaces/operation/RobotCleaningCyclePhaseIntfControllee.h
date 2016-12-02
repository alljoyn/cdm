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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEE_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface Controllee class
 */
class RobotCleaningCyclePhaseIntfControllee : public RobotCleaningCyclePhaseInterface {
  public:
    /**
     * Constructor of RobotCleaningCyclePhaseIntfControllee
     */
    RobotCleaningCyclePhaseIntfControllee() {}

    /**
     * Destructor of RobotCleaningCyclePhaseIntfControllee
     */
    virtual ~RobotCleaningCyclePhaseIntfControllee() {}

    /**
     * Get cycle phase
     * @return Cycle phase
     */
    virtual const uint8_t GetCyclePhase() const = 0;

    /**
     * Set cycle phase
     * @param[in] cyclePhase cycle phase
     * @return ER_OK on success
     */
    virtual QStatus SetCyclePhase(uint8_t cyclePhase) = 0;

    /**
     * Get supported cycle phases
     * @return Supported cycle phases
     */
    virtual const SupportedCyclePhases& GetSupportedCyclePhases() const = 0;

    /**
     * Set supported cycle phases
     * @param[in] supportedCyclePhases supported cycle phases
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedCyclePhases(const SupportedCyclePhases& supportedCyclePhases) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEE_H_ */