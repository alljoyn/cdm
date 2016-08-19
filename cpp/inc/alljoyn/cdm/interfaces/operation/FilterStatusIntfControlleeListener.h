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
#include <alljoyn/hae/interfaces/HaeInterfaceErrors.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controllee Listener class
 */
class FilterStatusIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of FilterStatusIntfControlleeListener
     */
    virtual ~FilterStatusIntfControlleeListener() {}

    /**
     * Handler for getting expected life in days
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] expectedLifeInDays expected life in days
     * @return ER_OK on success
     */
    virtual QStatus OnGetExpectedLifeInDays(uint16_t& expectedLifeInDays) = 0;

    /**
     * Handler for getting is cleanable
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] isCleanable is cleanable
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsCleanable(bool& isCleanable) = 0;

    /**
     * Handler for getting order percentage
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value order percentage
     * @return ER_OK on success
     */
    virtual QStatus OnGetOrderPercentage(uint8_t& value) = 0;

    /**
     * Handler for getting manufacturer
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] manufacturer manufacturer
     * @return ER_OK on success
     */
    virtual QStatus OnGetManufacturer(qcc::String& manufacturer) = 0;

    /**
     * Handler for getting part number
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] partNumber part number
     * @return ER_OK on success
     */
    virtual QStatus OnGetPartNumber(qcc::String& partNumber) = 0;

    /**
     * Handler for getting url
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] url url
     * @return ER_OK on success
     */
    virtual QStatus OnGetUrl(qcc::String& url) = 0;

    /**
     * Handler for getting life remaining
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value life remaining
     * @return ER_OK on success
     */
    virtual QStatus OnGetLifeRemaining(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLEELISTENER_H_ */
