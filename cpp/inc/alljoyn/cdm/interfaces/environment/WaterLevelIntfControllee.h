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

#ifndef WATERLEVELINTFCONTROLLEE_H_
#define WATERLEVELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelInterface.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface Controllee class
 */
class WaterLevelIntfControllee : public WaterLevelInterface {
  public:
    /**
     * Constructor of WaterLevelIntfControllee
     */
    WaterLevelIntfControllee() {}

    /**
     * Destructor of WaterLevelIntfControllee
     */
    virtual ~WaterLevelIntfControllee() {}

    /**
     * Get Current water Level
     * @return Current water Level
     */
    virtual const uint8_t GetCurrentLevel() const = 0;

    /**
     * Set CurrentLevel
     * @param[in] currentLevel current level
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentLevel (const uint8_t currentLevel) = 0;

    /**
     * Get max water level
     * @return max water level
     */
    virtual const uint8_t GetMaxLevel() const = 0;

    /**
     * Set MaxLevel
     * @param[in] maxLevel max level
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(const uint8_t maxLevel) = 0;

    /**
     * Get supply source
     * @return supply source
     */
    virtual const SupplySource GetSupplySource() const = 0;

    /**
     * Set SupplySource
     * @param[in] supplySource supplySource
     * @return ER_OK on success
     */
    virtual QStatus SetSupplySource(const SupplySource supplySource) = 0;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLEE_H_ */
