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

#ifndef RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_
#define RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedInterface.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controller Listener class
 */
class RapidModeTimedIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of RapidModeTimedIntfControllerListener
     */
    virtual ~RapidModeTimedIntfControllerListener() {}

    /**
     * Callback handler for GetRapidModeMinutesRemaining completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of RapidModeMinutesRemaining
     *                  (Time remaining in rapid mode. Zero indicates not in rapid mode.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for RapidModeMinutesRemaining property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of RapidModeMinutesRemaining
     *                  (Time remaining in rapid mode. Zero indicates not in rapid mode.)
     */
    virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for SetRapidModeMinutesRemaining completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetMaxSetMinutes completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxSetMinutes
     *                  (Maximum rapid mode set time. It does not change to accomodate already in rapid mode.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for MaxSetMinutes property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxSetMinutes
     *                  (Maximum rapid mode set time. It does not change to accomodate already in rapid mode.)
     */
    virtual void OnMaxSetMinutesChanged(const qcc::String& objectPath, const uint16_t value) {}
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_ */
