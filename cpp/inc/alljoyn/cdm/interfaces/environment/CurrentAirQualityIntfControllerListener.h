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

#ifndef CURRENTAIRQUALITYINTFCONTROLLERLISTENER_H_
#define CURRENTAIRQUALITYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controller Listener class
 */
class CurrentAirQualityIntfControllerListener : public InterfaceControllerListener {
  public:
    using ContaminantType = CurrentAirQualityInterface::ContaminantType;

    /**
     * Destructor of CurrentAirQualityIntfControllerListener
     */
    virtual ~CurrentAirQualityIntfControllerListener() {}

    /**
     * Callback handler for GetContaminantType completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of ContaminantType
     *                  (The contaminant type.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context) {}

    /**
     * Handler for ContaminantType property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of ContaminantType
     *                  (The contaminant type.)
     */
    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value) {}

    /**
     * Callback handler for GetCurrentValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentValue
     *                  (The current value of air quality.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentValue
     *                  (The current value of air quality.)
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetMinValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MinValue
     *                  (The minimum value allowed for CurrentValue.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for MinValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MinValue
     *                  (The minimum value allowed for CurrentValue.)
     */
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetMaxValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxValue
     *                  (The maximum value allowed for CurrentValue.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxValue
     *                  (The maximum value allowed for CurrentValue.)
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetPrecision completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Precision
     *                  (The precision of the CurrentValue property.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Precision
     *                  (The precision of the CurrentValue property.)
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetUpdateMinTime completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of UpdateMinTime
     *                  (The minimum time between updates of the CurrentValue property in milliseconds.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of UpdateMinTime
     *                  (The minimum time between updates of the CurrentValue property in milliseconds.)
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLERLISTENER_H_ */
