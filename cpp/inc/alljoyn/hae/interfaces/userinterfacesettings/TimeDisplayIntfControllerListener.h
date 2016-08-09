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
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controller Listener class
 */
class TimeDisplayIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~TimeDisplayIntfControllerListener() {}

    /**
     * Callback handler for getting DisplayTimeFormat
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] timeformat time format
     * @param[in] context the context that is passed from application
     */
    virtual void GetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t timeformat, void* context) {};

    /**
     * Callback handler for setting DisplayTimeFormat
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void SetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {};

    /**
     * Callback handler for getting SupportedDisplayTimeFormats
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supportedTimeFormats supportedTimeFormats
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedDisplayTimeFormatsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats, void* context) {};


    /**
     * Handler for DisplayTimeFormat property changed
     * @param[in] objectPath the object path
     * @param[in] timeformat timeformat
     */
    virtual void DisplayTimeFormatPropertyChanged(const qcc::String& objectPath, const uint8_t timeformat) {};

    /**
     * Handler for SupportedDisplayTimeFormats property changed
     * @param[in] objectPath the object path
     * @param[in] supportedTimeFormats supportedTimeFormats
     */
    virtual void SupportedDisplayTimeFormatsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats) {};

};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLERLISTENER_H_ */
