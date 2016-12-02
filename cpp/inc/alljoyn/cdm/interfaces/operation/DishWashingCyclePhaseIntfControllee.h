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

#ifndef DISHWASHINGCYCLEPHASEINTFCONTROLLEE_H_
#define DISHWASHINGCYCLEPHASEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface Controllee class
 */
class DishWashingCyclePhaseIntfControllee : public DishWashingCyclePhaseInterface {
  public:
    /**
     * Constructor of DishWashingCyclePhaseIntfControllee
     */
    DishWashingCyclePhaseIntfControllee() {}

    /**
     * Destructor of DishWashingCyclePhaseIntfControllee
     */
    virtual ~DishWashingCyclePhaseIntfControllee() {}

    /**
     * Get CyclePhase
     * @return current cycle phase
     */
    virtual const uint8_t GetCyclePhase() const = 0;

    /**
     * Set CyclePhase
     * @param[in]  cyclePhase the cycle phase to set
     * @return ER_OK on success
     */
    virtual QStatus SetCyclePhase(const uint8_t cyclePhase) = 0;

    /**
     * Get SupportedCyclePhases
     * @return the list of supported cycle phases
     */
    virtual const SupportedCyclePhases& GetSupportedCyclePhases() const = 0;

    /**
     * Set OperationalState
     * @param[in]  supportedCyclePhases the list of supported cycle phases to set
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedCyclePhases(const SupportedCyclePhases& supportedCyclePhases) = 0;

    /**
     * Set VendorDefinedCyclePhases
     * @param[in]  vendorPhases the list of vendor defined cycle phases to set
     * @return ER_OK on success
     */
    virtual QStatus SetVendorDefinedCyclePhases(const std::vector<uint8_t>& vendorPhases) = 0;

};

} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTFCONTROLLEE_H_ */