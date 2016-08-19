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

#ifndef TIMEDISPLAYINTFCONTROLLEE_H_
#define TIMEDISPLAYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/userinterfacesettings/TimeDisplayInterface.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controllee class
 */
class TimeDisplayIntfControllee : public TimeDisplayInterface {
  public:
    /**
     * Constructor of TimeDisplayIntfControllee
     */
    TimeDisplayIntfControllee() {}

    /**
     * Destructor of TimeDisplayIntfControllee
     */
    virtual ~TimeDisplayIntfControllee() {}
    
    /**
     * Get DisplayTimeFormat
     * @return display time format
     */
    virtual const uint8_t GetDisplayTimeFormat() = 0;

    /**
     * Set DisplayTimeFormat
     * @param[in] timeFormat timeFormat
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t timeFormat) = 0;

    /**
     * Get SupportedDisplayTimeFormats
     * @return list of supported time formats
     */
    virtual const std::vector<uint8_t>& GetSupportedDisplayTimeFormats() = 0;

    /**
     * Set SupportedDisplayTimeFormats
     * @param[in] supportedTimeFormats list of supported time formats
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayTimeFormats(const std::vector<uint8_t>& supportedTimeFormats) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLEE_H_ */
