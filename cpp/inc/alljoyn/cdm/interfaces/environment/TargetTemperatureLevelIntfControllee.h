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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLEE_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel Interface Controllee class
 */
class TargetTemperatureLevelIntfControllee : public TargetTemperatureLevelInterface {
  public:

    /**
     * Constructor of TargetTemperatureLevelIntfControllee
     */
    TargetTemperatureLevelIntfControllee() {}

    /**
     * Destructor of TargetTemperatureLevelIntfControllee
     */
    virtual ~TargetTemperatureLevelIntfControllee() {}

    /**
     * Get target temperature level
     * @return Target temperature level
     */
    virtual const uint8_t GetTargetLevel() const = 0;

    /**
     * Set target temperature level
     * @param[in] value the target temperature level
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(const uint8_t value) = 0;

    /**
     * Get the maximum value of target temperature level
     * @return The maximum value of target temperature level
     */
    virtual const uint8_t GetMaxLevel() const = 0;

    /**
     * Set the maximum value of target temperature level
     * @param[in] value the maximum value of target temperature level
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(const uint8_t value) = 0;

    /**
     * Get the selectable temperature level
     * @return The selectable temperature level
     */
    virtual const TargetTemperatureLevelInterface::TemperatureLevels& GetSelectableTemperatureLevels() const = 0;

    /**
     * Set the selectable temperature level
     * @param[in] value the selectable temperature level
     * @return ER_OK on success
     */
    virtual QStatus SetSelectableTemperatureLevels(const TargetTemperatureLevelInterface::TemperatureLevels& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLEE_H_ */
