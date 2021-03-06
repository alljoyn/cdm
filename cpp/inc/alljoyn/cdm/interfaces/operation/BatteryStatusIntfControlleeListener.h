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

#ifndef BATTERYSTATUSINTFCONTROLLEELISTENER_H_
#define BATTERYSTATUSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controllee Listener class
 */
class BatteryStatusIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of BatteryStatusIntfControlleeListener
     */
    virtual ~BatteryStatusIntfControlleeListener() {}

    /**
     * Handler for getting current value of battery status
     * @param[in] value current value
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentValue(uint8_t& value) = 0;

    /**
     * Handler for getting IsCharging property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] isCharging if battery is being charged or not
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsCharging(bool& isCharging) = 0;
};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLEELISTENER_H_ */
