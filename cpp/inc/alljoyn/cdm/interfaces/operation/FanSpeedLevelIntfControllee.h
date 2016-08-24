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

#ifndef FANSPEEDLEVELINTFCONTROLLEE_H_
#define FANSPEEDLEVELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controllee class
 */
class FanSpeedLevelIntfControllee : public FanSpeedLevelInterface {
  public:
    /**
     * Constructor of FanSpeedLevelIntfControllee
     */
    FanSpeedLevelIntfControllee() {}

    /**
     * Destructor of FanSpeedLevelIntfControllee
     */
    virtual ~FanSpeedLevelIntfControllee() {}

    /**
     * Get FanSpeedLevel
     * @return FanSpeedLevel
     */
    virtual const uint8_t GetFanSpeedLevel() const = 0;

    /**
     * Set FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus SetFanSpeedLevel (const uint8_t value) = 0;

    /**
     * Get MaxFanSpeedLevel
     * @return MaxFanSpeedLevel
     */
    virtual const uint8_t GetMaxFanSpeedLevel() const = 0;

    /**
     * Set MaxFanSpeedLevel
     * @param[in] MaxFanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus SetMaxFanSpeedLevel(const uint8_t value) = 0;

    /**
     * Get AutoMode
     * @return AutoMode
     */
    virtual const uint8_t GetAutoMode() const = 0;

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const uint8_t value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEE_H_ */
