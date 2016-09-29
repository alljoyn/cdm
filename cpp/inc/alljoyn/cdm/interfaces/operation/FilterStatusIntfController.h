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

#ifndef FILTERSTATUSINTFCONTROLLER_H_
#define FILTERSTATUSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusInterface.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controller class
 */
class FilterStatusIntfController : public FilterStatusInterface {
  public:
    /**
     * Constructor of FilterStatusIntfController
     */
    FilterStatusIntfController() {}

    /**
     * Destructor of FilterStatusIntfController
     */
    virtual ~FilterStatusIntfController() {}

    /**
     * Get ExpectedLifeInDays property
     * (Days a new filter will last. Used to convert percentage into remaining days. If 0xFFFF there is no predicted life. If 0 the life is less than 1 day.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetExpectedLifeInDays(void* context = NULL) = 0;

    /**
     * Get IsCleanable property
     * (This is a static property of the filter.  If the property is true a new filter does not need to be ordered, just clean.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsCleanable(void* context = NULL) = 0;

    /**
     * Get OrderPercentage property
     * (LifeRemaining it is recommended that a new filter be orderedIt can have a value of 0 because the remaining life is unpredictable, for example a psid switch. It can also have a value of 255 if OrderPercentage is N/A, for example a cleanable filter.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOrderPercentage(void* context = NULL) = 0;

    /**
     * Get Manufacturer property
     * (Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetManufacturer(void* context = NULL) = 0;

    /**
     * Get PartNumber property
     * (Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPartNumber(void* context = NULL) = 0;

    /**
     * Get Url property
     * (Url can be just a domain or a complete URL to the exact filter. It may provide additional information of a site for ordering. A null string is acceptable.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetUrl(void* context = NULL) = 0;

    /**
     * Get LifeRemaining property
     * (Lifespan Remaining in percentage (100 - 0). 0 indicates replace/clean. A simple device may just implement 100/0 or 100/OrderPercentage/0 instead of implementing the entire range of values.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetLifeRemaining(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLER_H_ */
