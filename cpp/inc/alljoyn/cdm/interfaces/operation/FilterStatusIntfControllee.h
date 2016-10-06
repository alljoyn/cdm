/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef FILTERSTATUSINTFCONTROLLEE_H_
#define FILTERSTATUSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusInterface.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controllee class
 */
class FilterStatusIntfControllee : public FilterStatusInterface {
  public:
    /**
     * Constructor of FilterStatusIntfControllee
     */
    FilterStatusIntfControllee() {}

    /**
     * Destructor of FilterStatusIntfControllee
     */
    virtual ~FilterStatusIntfControllee() {}

    /**
     * Get expected life in days
     * @return Expected life in days
     */
    virtual const uint16_t GetExpectedLifeInDays() const = 0;

    /**
     * Set expected life in days
     * @param[in] value expected life in days
     * @return ER_OK on success
     */
    virtual QStatus SetExpectedLifeInDays(const uint16_t value) = 0;

    /**
     * Get is cleanable
     * @return Is cleanable
     */
    virtual const bool GetIsCleanable() const = 0;

    /**
     * Set is cleanable
     * @param[in] isCleanable is cleanable
     * @return ER_OK on success
     */
    virtual QStatus SetIsCleanable(const bool isCleanable) = 0;

    /**
     * Get order percentage
     * @return Order percentage
     */
    virtual const uint8_t GetOrderPercentage() const = 0;

    /**
     * Set order percentage
     * @param[in] value order percentage
     * @return ER_OK on success
     */
    virtual QStatus SetOrderPercentage(const uint8_t value) = 0;

    /**
     * Get manufacturer
     * @return Manufacturer
     */
    virtual const qcc::String GetManufacturer() const = 0;

    /**
     * Set manufacturer
     * @param[in] manufacturer manufacturer
     * @return ER_OK on success
     */
    virtual QStatus SetManufacturer(const qcc::String& manufacturer) = 0;

    /**
     * Get part number
     * @return Part number
     */
    virtual const qcc::String GetPartNumber() const = 0;

    /**
     * Set part number
     * @param[in] partNumber part number
     * @return ER_OK on success
     */
    virtual QStatus SetPartNumber(const qcc::String& partNumber) = 0;

    /**
     * Get url
     * @return Url
     */
    virtual const qcc::String GetUrl() const = 0;

    /**
     * Set url
     * @param[in] url url
     * @return ER_OK on success
     */
    virtual QStatus SetUrl(const qcc::String& url) = 0;

    /**
     * Get life remaining
     * @return Life remaining
     */
    virtual const uint8_t GetLifeRemaining() const = 0;

    /**
     * Set life remaining
     * @param[in] value life remaining
     * @return ER_OK on success
     */
    virtual QStatus SetLifeRemaining(const uint8_t value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLEE_H_ */