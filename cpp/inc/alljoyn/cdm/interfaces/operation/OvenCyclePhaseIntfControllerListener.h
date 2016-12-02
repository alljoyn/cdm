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

#ifndef OVENCYCLEPHASEINTFCONTROLLERLISTENER_H_
#define OVENCYCLEPHASEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/OvenCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * OvenCyclePhase Interface Controller Listener class
 */
class OvenCyclePhaseIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~OvenCyclePhaseIntfControllerListener() {}

    /**
     * Callback handler for getting CyclePhase property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] cycle phase current cycle phase
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context) {}

    /**
     * Callback handler for getting list of supported cyclePhases
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] listOfCyclePhases list of supported cycle phases
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const OvenCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context) {}

    /**
     * Handler for CyclePhase property changed
     * @param[in] objectPath the object path
     * @param[in] cyclePhase current cycle phase
     */
    virtual void OnCyclePhasePropertyChanged(const qcc::String& objectPath, const uint8_t cyclePhase) {}

    /**
     * Handler for SupportedCyclePhases property changed
     * @param[in] objectPath the object path
     * @param[in] listOfCyclePhases list of cycle phases
     */
    virtual void OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const OvenCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases) {}

    /**
     * Callback handler for GetCyclePhasesDescriptions method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     * @param[out]listOfCycleDescriptions list of cycle phases descriptions
     */
    virtual void OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions,
                                                      void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* OVENCYCLEPHASEINTFCONTROLLERLISTENER_H_ */