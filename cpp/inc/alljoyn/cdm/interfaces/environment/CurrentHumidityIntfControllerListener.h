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

#ifndef CURRENTHUMIDITYINTFCONTROLLERLISTENER_H_
#define CURRENTHUMIDITYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity Interface Controller Listener class
 */
class CurrentHumidityIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of CurrentHumidityIntfControllerListener
     */
    virtual ~CurrentHumidityIntfControllerListener() {}

    /**
     * Callback handler for GetCurrentValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentValue
     *                  (Current relative humidity value)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentValue
     *                  (Current relative humidity value)
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetMaxValue completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxValue
     *                  (Maximum value allowed for represented relative humidity)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxValue
     *                  (Maximum value allowed for represented relative humidity)
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLERLISTENER_H_ */
