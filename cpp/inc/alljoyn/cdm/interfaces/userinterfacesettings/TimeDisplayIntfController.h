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

#ifndef TIMEDISPLAYINTFCONTROLLER_H_
#define TIMEDISPLAYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controller class
 */
class TimeDisplayIntfController : public TimeDisplayInterface {
  public:
    /**
     * Constructor of TimeDisplayIntfController
     */
    TimeDisplayIntfController() {}

    /**
     * Destructor of TimeDisplayIntfController
     */
    virtual ~TimeDisplayIntfController() {}

    /**
     * Get DisplayTimeFormat property
     * (The clock format which is currently used to display time (0=12-hour, 1=24-hour))
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTimeFormat(void* context = NULL) = 0;

    /**
     * Set DisplayTimeFormat property
     * (The clock format which is currently used to display time (0=12-hour, 1=24-hour))
     * @param[in] value The display time format to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t value, void* context = NULL) = 0;

    /**
     * Get SupportedDisplayTimeFormats property
     * (List of supported clock formats)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTimeFormats(void* context = NULL) = 0;
};

typedef std::shared_ptr<TimeDisplayIntfController> TimeDisplayIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLER_H_ */
