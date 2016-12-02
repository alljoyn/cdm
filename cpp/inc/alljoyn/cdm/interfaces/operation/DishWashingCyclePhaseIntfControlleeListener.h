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

#ifndef DISHWASHINGCYCLEPHASEINTFCONTROLLEELISTENER_H_
#define DISHWASHINGCYCLEPHASEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface Controllee Listener class
 */
class DishWashingCyclePhaseIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of DishWashingCyclePhaseIntfControlleeListener
     */
    virtual ~DishWashingCyclePhaseIntfControlleeListener() {}

    /**
     * Handler for getting current cycle phase
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] cyclePhase cyclePhase
     * @return ER_OK on success
     */
    virtual QStatus OnGetCyclePhase(uint8_t& cyclePhase) = 0;

    /**
     * Handler for getting list of supported cycle phases
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] listOfSupportedCyclePhases list of supported cycle phases
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedCyclePhases(DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfSupportedCyclePhases) = 0;

    /**
     * Handler for getting list cycle phases descriptions
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[in] language language
     * @param[out] listOfPhaseDescs list of cycle phases descriptions
     * @return ER_OK on success
     */
    virtual QStatus OnGetCyclePhasesDescriptions(const qcc::String& language,
                                                 DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfPhaseDescs,
                                                 ErrorCode& errorCode) = 0;

};

} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTFCONTROLLEELISTENER_H_ */