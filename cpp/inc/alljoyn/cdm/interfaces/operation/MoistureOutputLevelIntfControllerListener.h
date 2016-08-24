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

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel interface controller listener class
 */
class MoistureOutputLevelIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of MoistureOutputLevelIntfControllerListener
     */
    virtual ~MoistureOutputLevelIntfControllerListener() {}

    /**
     * Handler for MoistureOutputLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value moisture output level
     */
    virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxMoistureOutputLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum moisture output level
     */
    virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for AutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] autoMode auto mode
     */
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t autoMode) {}

    /**
     * Callback handler for getting MoistureOutputLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value moisture output level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for setting MoistureOutputLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting MaxMoistureOutputLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum moisture output level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting AutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] autoMode auto mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t autoMode, void* context) {}

    /**
     * Callback handler for setting AutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_ */
