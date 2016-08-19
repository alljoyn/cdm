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

#ifndef TIMEDISPLAYINTFCONTROLLEELISTENER_H_
#define TIMEDISPLAYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterfaceErrors.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controllee Listener class
 */
class TimeDisplayIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of TimeDisplayIntfControlleeListener
     */
    virtual ~TimeDisplayIntfControlleeListener() {}

    /**
     * Handler for setting DisplayTimeFormat property
     * @param[in] timeFormat time format
     * @return ER_OK on success
     */
    virtual QStatus OnSetDisplayTimeFormat(const uint8_t timeFormat) = 0;

    /**
     * Handler for getting DisplayTimeFormat property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] timeFormat time format
     * @return ER_OK on success
     */
    virtual QStatus OnGetDisplayTimeFormat(uint8_t& timeFormat) = 0;

    /**
     * Handler for getting SupportedDisplayTimeFormats
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] selectableLevels the list of selectable levels
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedDisplayTimeFormats(std::vector<uint8_t>& supportedDisplayTimeFormats) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLEELISTENER_H_ */
