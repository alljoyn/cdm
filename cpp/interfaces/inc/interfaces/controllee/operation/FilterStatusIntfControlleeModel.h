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

#ifndef FILTERSTATUSINTFCONTROLLEELISTENER_H_
#define FILTERSTATUSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/FilterStatusInterface.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Model Interface class for the Controllee
 */
class FilterStatusIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of FilterStatusIntfControlleeModel
     */
    virtual ~FilterStatusIntfControlleeModel() {}

    /**
     * Get ExpectedLifeInDays
     * @return current expected life in days
     */
    virtual QStatus GetExpectedLifeInDays(uint16_t& out) const = 0;
    /**
     * Get IsCleanable
     * @return current is cleanable
     */
    virtual QStatus GetIsCleanable(bool& out) const = 0;
    /**
     * Get OrderPercentage
     * @return current order percentage
     */
    virtual QStatus GetOrderPercentage(uint8_t& out) const = 0;
    /**
     * Get Manufacturer
     * @return current manufacturer
     */
    virtual QStatus GetManufacturer(qcc::String& out) const = 0;
    /**
     * Get PartNumber
     * @return current part number
     */
    virtual QStatus GetPartNumber(qcc::String& out) const = 0;
    /**
     * Get Url
     * @return current url
     */
    virtual QStatus GetUrl(qcc::String& out) const = 0;
    /**
     * Get LifeRemaining
     * @return current life remaining
     */
    virtual QStatus GetLifeRemaining(uint8_t& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLEELISTENER_H_ */
