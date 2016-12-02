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

#ifndef SOILLEVELINTFCONTROLLERLISTENER_H_
#define SOILLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelInterface.h>

namespace ajn {
namespace services {

/**
 * SoilLevel Interface Controller Listener class
 */
class SoilLevelIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of SoilLevelIntfControllerListener
     */
    virtual ~SoilLevelIntfControllerListener() {}

    /**
     * Callback handler for GetMaxLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxLevel
     *                  (Maximum value allowed for target soil level setting.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxLevel
     *                  (Maximum value allowed for target soil level setting.)
     */
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetTargetLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetLevel
     *                  (Target set-point value of soil level.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for TargetLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetLevel
     *                  (Target set-point value of soil level.)
     */
    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetTargetLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetSelectableLevels completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SelectableLevels
     *                  (List of the values of soil level which can be selected.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSelectableLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for SelectableLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SelectableLevels
     *                  (List of the values of soil level which can be selected.)
     */
    virtual void OnSelectableLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* SOILLEVELINTFCONTROLLERLISTENER_H_ */
