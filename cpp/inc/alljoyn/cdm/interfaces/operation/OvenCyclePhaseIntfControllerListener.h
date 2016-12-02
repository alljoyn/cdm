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
    using CyclePhaseDescriptor = OvenCyclePhaseInterface::CyclePhaseDescriptor;

    /**
     * Destructor of OvenCyclePhaseIntfControllerListener
     */
    virtual ~OvenCyclePhaseIntfControllerListener() {}

    /**
     * Callback handler for GetCyclePhase completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CyclePhase
     *                  (Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for CyclePhase property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CyclePhase
     *                  (Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer)
     */
    virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetSupportedCyclePhases completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedCyclePhases
     *                  (List of supported cycle phases.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for SupportedCyclePhases property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedCyclePhases
     *                  (List of supported cycle phases.)
     */
    virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}

    /**
     * Callback handler for GetVendorPhasesDescription completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] phasesDescription Cycle phases description.
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const std::vector<CyclePhaseDescriptor>& phasesDescription, void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* OVENCYCLEPHASEINTFCONTROLLERLISTENER_H_ */
