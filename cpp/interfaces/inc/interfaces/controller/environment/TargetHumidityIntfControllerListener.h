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

// This file is automatically generated. Do not edit it.

#ifndef TARGETHUMIDITYINTFCONTROLLERLISTENER_H_
#define TARGETHUMIDITYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity Interface Controller Listener class
 */
class TargetHumidityIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TargetHumidityIntfControllerListener
     */
    virtual ~TargetHumidityIntfControllerListener() {}

    /**
     * Callback handler for GetTargetValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetValue
     *                  (Target set-point value of relative humidity.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for TargetValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of TargetValue
     *                  (Target set-point value of relative humidity.)
     */
    virtual void OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetTargetValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetMinValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MinValue
     *                  (Minimum value allowed for the TargetValue.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MinValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MinValue
     *                  (Minimum value allowed for the TargetValue.)
     */
    virtual void OnMinValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetMaxValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxValue
     *                  (Maximum value allowed for the TargetValue.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxValue
     *                  (Maximum value allowed for the TargetValue.)
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetStepValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of StepValue
     *                  (Step value allowed for the TargetValue setting.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for StepValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of StepValue
     *                  (Step value allowed for the TargetValue setting.)
     */
    virtual void OnStepValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetSelectableHumidityLevels completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SelectableHumidityLevels
     *                  (List of the selectable levels of target humidity. The list is only available when this interface is implemented for setting a qualitative level of target humidity. (When MinValue = MaxValue))
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for SelectableHumidityLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SelectableHumidityLevels
     *                  (List of the selectable levels of target humidity. The list is only available when this interface is implemented for setting a qualitative level of target humidity. (When MinValue = MaxValue))
     */
    virtual void OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLERLISTENER_H_ */
