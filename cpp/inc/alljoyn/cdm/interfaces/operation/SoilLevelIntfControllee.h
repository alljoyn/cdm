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

#ifndef SOILLEVELINTFCONTROLLEE_H_
#define SOILLEVELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelInterface.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * SoilLevel Interface Controllee class
 */
class SoilLevelIntfControllee : public SoilLevelInterface {
  public:
    /**
     * Constructor of SoilLevelIntfControllee
     */
    SoilLevelIntfControllee() {}

    /**
     * Destructor of SoilLevelIntfControllee
     */
    virtual ~SoilLevelIntfControllee() {}

    /**
     * Get MaxLevel
     * @return MaxLevel
     */
    virtual const uint8_t GetMaxLevel() const = 0;

    /**
     * Set MaxLevel
     * @param[in] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(uint8_t maxLevel) = 0;

    /**
     * Get TargetLevel
     * @return TargetLevel
     */
    virtual const uint8_t GetTargetLevel () const = 0;

    /**
     * Set TargetLevel
     * @param[in] targetLevel targetLevel
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(uint8_t targetLevel) = 0;

    /**
     * Get SelectableLevels
     * @return The list of selectable levels
     */
    virtual const std::vector<uint8_t>& GetSelectableLevels() const = 0;

    /**
     * Set SelectableLevels
     * @param[in] selectableLevels the list of levels
     * @return ER_OK on success
     */
    virtual QStatus SetSelectableLevels(const std::vector<uint8_t>& selectableLevels) = 0;
};

} //namespace services
} //namespace ajn

#endif /* SOILLEVELINTFCONTROLLEE_H_ */
