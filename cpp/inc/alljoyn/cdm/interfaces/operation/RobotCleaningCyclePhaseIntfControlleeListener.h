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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include "RobotCleaningCyclePhaseInterface.h"

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface Controllee Listener class
 */
class RobotCleaningCyclePhaseIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RobotCleaningCyclePhaseIntfControlleeListener
     */
    virtual ~RobotCleaningCyclePhaseIntfControlleeListener() {}

    /**
     * Handler for getting CyclePhase property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] cyclePhase cycle phase
     * @return ER_OK on success
     */
    virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase) = 0;

    /**
     * Handler for getting SupportedCyclePhases property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedCyclePhases supported cycle phases
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedCyclePhases(RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases) = 0;

    /**
     * Handler for GetVendorPhasesDescription method
     * @param[in] languageTag language tag
     * @param[out] phasesDescription the list of cycle phases description
     * @param[out] errorCode the error code should be set when the method call is failed
     * @return ER_OK on succes
     */
    virtual QStatus OnGetVendorPhasesDescription(const qcc::String& languageTag,
                                                 RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                 ErrorCode& errorCode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEELISTENER_H_ */