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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERLISTENER_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include "RobotCleaningCyclePhaseInterface.h"

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface Controller Listener class
 */
class RobotCleaningCyclePhaseIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RobotCleaningCyclePhaseIntfControllerListener() {}

    /**
     * Callback handler for getting CyclePhase property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] cyclePhase cycle phase
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t cyclePhase, void* context) {}

    /**
     * Callback handler for getting SupportedCyclePhases property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supportedCyclePhases supported cycle phases
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath,
                                                   const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases, void* context) {}

    /**
     * Callback handler for GetVendorPhasesDescription method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] phasesDescription the list of cycle phases description
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath,
                                                      const RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                      void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Handler for CyclePhase property changed
     * @param[in] objectPath the object path
     * @param[in] cyclePhase cycle phase
     */
    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase) {}

    /**
     * Handler for SupportedCyclePhases property changed
     * @param[in] objectPath the object path
     * @param[in] supportedCyclePhases supported cycle phases
     */
    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases) {}
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERLISTENER_H_ */