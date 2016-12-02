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

#ifndef FILTERSTATUSINTFCONTROLLERLISTENER_H_
#define FILTERSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusInterface.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controller Listener class
 */
class FilterStatusIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of FilterStatusIntfControllerListener
     */
    virtual ~FilterStatusIntfControllerListener() {}

    /**
     * Callback handler for GetExpectedLifeInDays completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of ExpectedLifeInDays
     *                  (Days a new filter will last. Used to convert percentage into remaining days. If 0xFFFF there is no predicted life. If 0 the life is less than 1 day.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for ExpectedLifeInDays property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of ExpectedLifeInDays
     *                  (Days a new filter will last. Used to convert percentage into remaining days. If 0xFFFF there is no predicted life. If 0 the life is less than 1 day.)
     */
    virtual void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for GetIsCleanable completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of IsCleanable
     *                  (This is a static property of the filter.  If the property is true a new filter does not need to be ordered, just clean.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for IsCleanable property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of IsCleanable
     *                  (This is a static property of the filter.  If the property is true a new filter does not need to be ordered, just clean.)
     */
    virtual void OnIsCleanableChanged(const qcc::String& objectPath, const bool value) {}

    /**
     * Callback handler for GetOrderPercentage completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of OrderPercentage
     *                  (LifeRemaining it is recommended that a new filter be orderedIt can have a value of 0 because the remaining life is unpredictable, for example a psid switch. It can also have a value of 255 if OrderPercentage is N/A, for example a cleanable filter.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for OrderPercentage property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of OrderPercentage
     *                  (LifeRemaining it is recommended that a new filter be orderedIt can have a value of 0 because the remaining life is unpredictable, for example a psid switch. It can also have a value of 255 if OrderPercentage is N/A, for example a cleanable filter.)
     */
    virtual void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetManufacturer completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Manufacturer
     *                  (Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) {}

    /**
     * Handler for Manufacturer property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Manufacturer
     *                  (Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.)
     */
    virtual void OnManufacturerChanged(const qcc::String& objectPath, const qcc::String& value) {}

    /**
     * Callback handler for GetPartNumber completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of PartNumber
     *                  (Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) {}

    /**
     * Handler for PartNumber property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of PartNumber
     *                  (Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.)
     */
    virtual void OnPartNumberChanged(const qcc::String& objectPath, const qcc::String& value) {}

    /**
     * Callback handler for GetUrl completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Url
     *                  (Url can be just a domain or a complete URL to the exact filter. It may provide additional information of a site for ordering. A null string is acceptable.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) {}

    /**
     * Handler for Url property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Url
     *                  (Url can be just a domain or a complete URL to the exact filter. It may provide additional information of a site for ordering. A null string is acceptable.)
     */
    virtual void OnUrlChanged(const qcc::String& objectPath, const qcc::String& value) {}

    /**
     * Callback handler for GetLifeRemaining completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of LifeRemaining
     *                  (Lifespan Remaining in percentage (100 - 0). 0 indicates replace/clean. A simple device may just implement 100/0 or 100/OrderPercentage/0 instead of implementing the entire range of values.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for LifeRemaining property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of LifeRemaining
     *                  (Lifespan Remaining in percentage (100 - 0). 0 indicates replace/clean. A simple device may just implement 100/0 or 100/OrderPercentage/0 instead of implementing the entire range of values.)
     */
    virtual void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value) {}
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLERLISTENER_H_ */
