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

#ifndef CURRENTTEMPERATUREINTFCONTROLLERLISTENER_H_
#define CURRENTTEMPERATUREINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentTemperature Interface Controller Listener class
 */
class CurrentTemperatureIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of CurrentTemperatureIntfControllerListener
     */
    virtual ~CurrentTemperatureIntfControllerListener() {}

    /**
     * Callback handler for GetCurrentValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentValue
     *                  (Current temperature expressed in Celsius.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentValue
     *                  (Current temperature expressed in Celsius.)
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value) {}

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

#endif /* CURRENTTEMPERATUREINTFCONTROLLERLISTENER_H_ */
