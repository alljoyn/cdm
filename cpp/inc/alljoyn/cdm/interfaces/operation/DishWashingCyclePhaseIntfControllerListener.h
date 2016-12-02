/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef DISHWASHINGCYCLEPHASEINTFCONTROLLERLISTENER_H_
#define DISHWASHINGCYCLEPHASEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface Controller Listener class
 */
class DishWashingCyclePhaseIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~DishWashingCyclePhaseIntfControllerListener() {}

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
    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context) {}

    /**
     * Handler for CyclePhase property changed
     * @param[in] objectPath the object path
     * @param[in] cyclePhase current cycle phase
     */
    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase) {}

    /**
     * Handler for SupportedCyclePhases property changed
     * @param[in] objectPath the object path
     * @param[in] listOfCyclePhases list of cycle phases
     */
    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases listOfCyclePhases) {}

    /**
     * Callback handler for GetCyclePhasesDescriptions method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     * @param[out]listOfCycleDescriptions list of cycle phases descriptions
     */
    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions,
                                                      void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTFCONTROLLERLISTENER_H_ */
