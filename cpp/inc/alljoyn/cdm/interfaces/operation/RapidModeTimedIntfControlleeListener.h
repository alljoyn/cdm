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

#ifndef RAPIDMODETIMEDINTFCONTROLLEELISTENER_H_
#define RAPIDMODETIMEDINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controllee Listener class
 */
class RapidModeTimedIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RapidModeTimedIntfControlleeListener
     */
    virtual ~RapidModeTimedIntfControlleeListener() {}

    /**
     * Handler for getting RapidModeMinutesRemaining property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value time remaining in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetRapidModeMinutesRemaining(uint16_t& value) = 0;

    /**
     * Handler for setting RapidModeMinutesRemaining property
     * @param[in] value time remaining in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetRapidModeMinutesRemaining(const uint16_t& value) = 0;

    /**
     * Handler for getting MaxSetMinutes property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum rapid mode set time
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxSetMinutes(uint16_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLEELISTENER_H_ */
