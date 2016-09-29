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

#ifndef CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_
#define CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface Controller Listener class
 */
class ClimateControlModeIntfControllerListener : public InterfaceControllerListener {
  public:
    using Mode = ClimateControlModeInterface::Mode;
    using OperationalState = ClimateControlModeInterface::OperationalState;

    /**
     * Destructor of ClimateControlModeIntfControllerListener
     */
    virtual ~ClimateControlModeIntfControllerListener() {}

    /**
     * Callback handler for GetMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Mode
     *                  (Current mode of device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context) {}

    /**
     * Handler for Mode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Mode
     *                  (Current mode of device.)
     */
    virtual void OnModeChanged(const qcc::String& objectPath, const Mode value) {}

    /**
     * Callback handler for SetMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetSupportedModes completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedModes
     *                  (Array of supported modes.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context) {}

    /**
     * Handler for SupportedModes property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedModes
     *                  (Array of supported modes.)
     */
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value) {}

    /**
     * Callback handler for GetOperationalState completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of OperationalState
     *                  (Current status of device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context) {}

    /**
     * Handler for OperationalState property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of OperationalState
     *                  (Current status of device.)
     */
    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value) {}
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_ */
