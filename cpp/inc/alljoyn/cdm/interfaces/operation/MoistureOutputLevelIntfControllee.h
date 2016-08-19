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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLEE_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLEE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel Interface Controllee class
 */
class MoistureOutputLevelIntfControllee : public MoistureOutputLevelInterface {
  public:
    /**
     * Constructor of MoistureOutputLevelIntfControllee
     */
    MoistureOutputLevelIntfControllee() {}

    /**
     * Destructor of MoistureOutputLevelIntfControllee
     */
    virtual ~MoistureOutputLevelIntfControllee() {}

    /**
     * Get moisture output level
     * @return Moisture output level
     */
    virtual const uint8_t GetMoistureOutputLevel() const = 0;

    /**
     * Set moisture output level
     * @param[in] value moisture output level
     * @return ER_OK on success
     */
    virtual QStatus SetMoistureOutputLevel(const uint8_t value) = 0;

    /**
     * Get the maximum moisture output level
     * @return The maximum moisture output level
     */
    virtual const uint8_t GetMaxMoistureOutputLevel() const = 0;

    /**
     * Set the maximum moisture output level
     * @param[in] value the maximum moisture output level
     * @return ER_OK on success
     */
    virtual QStatus SetMaxMoistureOutputLevel(const uint8_t value) = 0;

    /**
     * Get auto mode
     * @return Auto mode
     */
    virtual const uint8_t GetAutoMode () const = 0;

    /**
     * Set auto mode
     * @param[in] autoMode auto mode
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode (const uint8_t autoMode) = 0;
};

} //namespace services
} //namespace ajn


#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLEE_H_ */
