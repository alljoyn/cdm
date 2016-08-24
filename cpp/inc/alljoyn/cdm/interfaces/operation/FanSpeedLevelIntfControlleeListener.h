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

#ifndef FANSPEEDLEVELINTFCONTROLLEELISTENER_H_
#define FANSPEEDLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controllee Listener class
 */
class FanSpeedLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of FanSpeedLevelIntfControlleeListener
     */
    virtual ~FanSpeedLevelIntfControlleeListener() {}

    /**
     * Handler for setting FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus OnSetFanSpeedLevel(const uint8_t& value) = 0;

    /**
     * Handler for getting FanSpeedLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] FanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetFanSpeedLevel(uint8_t& value) = 0;

    /**
     * Handler for getting MaxFanSpeedLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] MaxFanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxFanSpeedLevel(uint8_t& value) = 0;

    /**
     * Handler for setting AutoMode
     * @param[in] AutoMode
     * @return ER_OK on success
     */
    virtual QStatus OnSetAutoMode(const uint8_t& value) = 0;

    /**
     * Handler for getting AutoMode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] AutoMode
     * @return ER_OK on success
     */
    virtual QStatus OnGetAutoMode(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEELISTENER_H_ */
