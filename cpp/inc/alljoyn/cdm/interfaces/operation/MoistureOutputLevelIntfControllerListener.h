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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel Interface Controller Listener class
 */
class MoistureOutputLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    using AutoMode = MoistureOutputLevelInterface::AutoMode;

    /**
     * Destructor of MoistureOutputLevelIntfControllerListener
     */
    virtual ~MoistureOutputLevelIntfControllerListener() {}

    /**
     * Callback handler for GetMoistureOutputLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MoistureOutputLevel
     *                  (Current level of moisture output.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MoistureOutputLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MoistureOutputLevel
     *                  (Current level of moisture output.)
     */
    virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetMoistureOutputLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetMaxMoistureOutputLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxMoistureOutputLevel
     *                  (Maximum level of moisture output.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxMoistureOutputLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxMoistureOutputLevel
     *                  (Maximum level of moisture output.)
     */
    virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of AutoMode
     *                  (Represent enabled/disabled state of the auto mode. The device decides the moisture output level for providing comfortable surroundings automatically.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context) {}

    /**
     * Handler for AutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of AutoMode
     *                  (Represent enabled/disabled state of the auto mode. The device decides the moisture output level for providing comfortable surroundings automatically.)
     */
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const AutoMode value) {}

    /**
     * Callback handler for SetAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_ */
