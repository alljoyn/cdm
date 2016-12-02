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

#ifndef SPINSPEEDLEVELINTFCONTROLLEELISTENER_H_
#define SPINSPEEDLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/SpinSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * SpinSpeedLevel Model Interface class for the Controllee
 */
class SpinSpeedLevelIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of SpinSpeedLevelIntfControlleeModel
     */
    virtual ~SpinSpeedLevelIntfControlleeModel() {}

    /**
     * Get MaxLevel
     * @return current max level
     */
    virtual QStatus GetMaxLevel(uint8_t& out) const = 0;
    /**
     * Get TargetLevel
     * @return current target level
     */
    virtual QStatus GetTargetLevel(uint8_t& out) const = 0;

     /**
     * Set TargetLevel
     * @param[in] value The target level to set
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(const uint8_t value) = 0;
    /**
     * Get SelectableLevels
     * @return current selectable levels
     */
    virtual QStatus GetSelectableLevels(std::vector<uint8_t>& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* SPINSPEEDLEVELINTFCONTROLLEELISTENER_H_ */
