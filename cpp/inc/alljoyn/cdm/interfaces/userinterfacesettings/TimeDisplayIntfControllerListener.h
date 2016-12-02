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

#ifndef TIMEDISPLAYINTFCONTROLLERLISTENER_H_
#define TIMEDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controller Listener class
 */
class TimeDisplayIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TimeDisplayIntfControllerListener
     */
    virtual ~TimeDisplayIntfControllerListener() {}

    /**
     * Callback handler for GetDisplayTimeFormat completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of DisplayTimeFormat
     *                  (The clock format which is currently used to display time (0=12-hour, 1=24-hour))
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetDisplayTimeFormat(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for DisplayTimeFormat property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of DisplayTimeFormat
     *                  (The clock format which is currently used to display time (0=12-hour, 1=24-hour))
     */
    virtual void OnDisplayTimeFormatChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetDisplayTimeFormat completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetDisplayTimeFormat(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetSupportedDisplayTimeFormats completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedDisplayTimeFormats
     *                  (List of supported clock formats)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedDisplayTimeFormats(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for SupportedDisplayTimeFormats property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedDisplayTimeFormats
     *                  (List of supported clock formats)
     */
    virtual void OnSupportedDisplayTimeFormatsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLERLISTENER_H_ */
