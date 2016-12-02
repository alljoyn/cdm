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
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Model Interface class for the Controllee
 */
class FanSpeedLevelIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:
    using AutoMode = FanSpeedLevelInterface::AutoMode;

    /**
     * Destructor of FanSpeedLevelIntfControlleeModel
     */
    virtual ~FanSpeedLevelIntfControlleeModel() {}

    /**
     * Get FanSpeedLevel
     * @return current fan speed level
     */
    virtual QStatus GetFanSpeedLevel(uint8_t& out) const = 0;

     /**
     * Set FanSpeedLevel
     * @param[in] value The fan speed level to set
     * @return ER_OK on success
     */
    virtual QStatus SetFanSpeedLevel(const uint8_t value) = 0;
    /**
     * Get MaxFanSpeedLevel
     * @return current max fan speed level
     */
    virtual QStatus GetMaxFanSpeedLevel(uint8_t& out) const = 0;
    /**
     * Get AutoMode
     * @return current auto mode
     */
    virtual QStatus GetAutoMode(AutoMode& out) const = 0;

     /**
     * Set AutoMode
     * @param[in] value The auto mode to set
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const AutoMode value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEELISTENER_H_ */
