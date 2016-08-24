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

#ifndef BATTERYSTATUSINTFCONTROLLERLISTENER_H_
#define BATTERYSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controller Listener class
 */
class BatteryStatusIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~BatteryStatusIntfControllerListener() {}

    /**
     * Callback handler for getting CurrentValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] volume volume
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t currentValue, void* context) {}

    /**
     * Callback handler for getting IsCharging property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isCharging if battery is being charged or not
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool isCharging, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] volume volume
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t currentValue) {}

    /**
     * Handler for IsCharging property changed
     * @param[in] objectPath the object path
     * @param[in] isCharging if batter is being charged or not
     */
    virtual void OnIsChargingChanged(const qcc::String& objectPath, const bool isCharging) {}

};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLERLISTENER_H_ */
