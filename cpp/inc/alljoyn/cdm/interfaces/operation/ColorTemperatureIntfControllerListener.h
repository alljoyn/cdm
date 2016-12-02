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

#ifndef COLORTEMPERATUREINTFCONTROLLERLISTENER_H_
#define COLORTEMPERATUREINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/ColorTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * ColorTemperature Interface Controller Listener class
 */
class ColorTemperatureIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of ColorTemperatureIntfControllerListener
     */
    virtual ~ColorTemperatureIntfControllerListener() {}

    /**
     * Callback handler for GetTemperature completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Temperature
     *                  (Color temperature of the device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for Temperature property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Temperature
     *                  (Color temperature of the device.)
     */
    virtual void OnTemperatureChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for SetTemperature completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTemperature(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetMinTemperature completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MinTemperature
     *                  (The minimum color temperature supported by the device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMinTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for MinTemperature property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MinTemperature
     *                  (The minimum color temperature supported by the device.)
     */
    virtual void OnMinTemperatureChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetMaxTemperature completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxTemperature
     *                  (The maximum color temperature supported by the device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for MaxTemperature property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxTemperature
     *                  (The maximum color temperature supported by the device.)
     */
    virtual void OnMaxTemperatureChanged(const qcc::String& objectPath, const double value) {}
};

} //namespace services
} //namespace ajn

#endif /* COLORTEMPERATUREINTFCONTROLLERLISTENER_H_ */
