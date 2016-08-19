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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLEE_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/operation/AirRecirculationModeInterface.h>

namespace ajn {
namespace services {

/**
 * AirRecirculationMode Interface Controllee class
 */
class AirRecirculationModeIntfControllee : public AirRecirculationModeInterface {
  public:
    /**
     * Constructor of AirRecirculationModeIntfControllee
     */
    AirRecirculationModeIntfControllee() {}

    /**
     * Destructor of AirRecirculationModeIntfControllee
     */
    virtual ~AirRecirculationModeIntfControllee() {}

    /**
     * Set if air is being recirculated
     * @param[in] isRecirculating if air is being recirculated or not
     * @return ER_OK on success
     */
    virtual QStatus SetIsRecirculating(const bool isRecirculating) = 0;

    /**
     * Get if air is being recirculated
     * @return If air is being recirculated or not
     */
    virtual const bool GetIsRecirculating() const = 0;
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLEE_H_ */
