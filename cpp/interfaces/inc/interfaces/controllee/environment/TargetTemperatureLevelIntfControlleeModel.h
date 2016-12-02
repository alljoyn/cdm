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

// This file is automatically generated. Do not edit it.

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLEELISTENER_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>
#include <interfaces/common/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel Model Interface class for the Controllee
 */
class TargetTemperatureLevelIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of TargetTemperatureLevelIntfControlleeModel
     */
    virtual ~TargetTemperatureLevelIntfControlleeModel() {}

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
     * Get SelectableTemperatureLevels
     * @return current selectable temperature levels
     */
    virtual QStatus GetSelectableTemperatureLevels(std::vector<uint8_t>& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLEELISTENER_H_ */
