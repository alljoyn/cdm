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

#ifndef CLIMATECONTROLMODEINTFCONTROLLEE_H_
#define CLIMATECONTROLMODEINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface Controllee class
 */
class ClimateControlModeIntfControllee : public ClimateControlModeInterface {
  public:
    /**
     * Constructor of ClimateControlMode
     */
    ClimateControlModeIntfControllee() {}

    /**
     * Destructor of ClimateControlMode
     */
    virtual ~ClimateControlModeIntfControllee() {}

    /**
     * Get mode
     * @return Mode
     */
    virtual const uint16_t GetMode() const = 0;

    /**
     * Set mode
     * @param[in] mode mode
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const uint16_t mode) = 0;

    /**
     * Get supported modes
     * @return Supported modes
     */
    virtual const SupportedModes& GetSupportedModes() const = 0;

    /**
     * Set supported modes
     * @param[in] modes supported modes
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedModes(const SupportedModes& modes) = 0;

    /**
     * Get operational state
     * @return Operational state
     */
    virtual const uint16_t GetOperationalState() const = 0;

    /**
     * Set operational state
     * @param[in] state operational state
     * @return ER_OK on success
     */
    virtual QStatus SetOperationalState(const uint16_t state) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLEE_H_ */
