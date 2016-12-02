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

#ifndef FANSPEEDLEVELINTFCONTROLLERLISTENER_H_
#define FANSPEEDLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controller Listener class
 */
class FanSpeedLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    using AutoMode = FanSpeedLevelInterface::AutoMode;

    /**
     * Destructor of FanSpeedLevelIntfControllerListener
     */
    virtual ~FanSpeedLevelIntfControllerListener() {}

    /**
     * Callback handler for GetFanSpeedLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of FanSpeedLevel
     *                  (Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for FanSpeedLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of FanSpeedLevel
     *                  (Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).)
     */
    virtual void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetFanSpeedLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetMaxFanSpeedLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxFanSpeedLevel
     *                  (Maximum level allowed for target fan speed level.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxFanSpeedLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxFanSpeedLevel
     *                  (Maximum level allowed for target fan speed level.)
     */
    virtual void OnMaxFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of AutoMode
     *                  (Enabled/disabled state of the auto mode.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context) {}

    /**
     * Handler for AutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of AutoMode
     *                  (Enabled/disabled state of the auto mode.)
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

#endif /* FANSPEEDLEVELINTFCONTROLLERLISTENER_H_ */
