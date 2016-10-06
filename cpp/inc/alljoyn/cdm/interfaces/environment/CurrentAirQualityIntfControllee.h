/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef CURRENTAIRQUALITYINTFCONTROLLEE_H_
#define CURRENTAIRQUALITYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controllee class
 */
class CurrentAirQualityIntfControllee : public CurrentAirQualityInterface {
  public:
    /**
     * Constructor of CurrentAirQualityIntfControllee
     */
    CurrentAirQualityIntfControllee() {}

    /**
     * Destructor of CurrentAirQualityIntfControllee
     */
    virtual ~CurrentAirQualityIntfControllee() {}

    /**
     * Get contaminant type
     * @return contaminant type
     */
    virtual const uint8_t GetContaminantType() const = 0;

    /**
     * Set contaminant type
     * @param[in] type contaminant type
     * @return ER_OK on success
     */
    virtual QStatus SetContaminantType(const uint8_t type) = 0;

    /**
     * Get current air quality
     * @return Current air quaility
     */
    virtual const double GetCurrentValue() const = 0;

    /**
     * Set current air qaulity
     * @param[in] value current air quality
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentValue(const double value) = 0;

    /**
     * Get the maximum value of air quality
     * @return The maximum value of air quality
     */
    virtual const double GetMaxValue() const = 0;

    /**
     * Set the maximum value of air quality
     * @param[in] value the maximum value of air quality
     * @return ER_OK on success
     */
    virtual QStatus SetMaxValue(const double value) = 0;

    /**
     * Get the minimum value of air quality
     * @return The minimum value of air quality
     */
    virtual const double GetMinValue() const = 0;

    /**
     * Set the minimum value of air quality
     * @param[in] value the minimum value of air quality
     * @return ER_OK on success
     */
    virtual QStatus SetMinValue(const double value) = 0;

    /**
     * Get precision
     * @return Precision
     */
    virtual const double GetPrecision() const = 0;

    /**
     * Set precision
     * @param[in] precision precision
     * @return ER_OK on success
     */
    virtual QStatus SetPrecision(const double precision) = 0;

    /**
     * Get the minimum update time
     * @return The minimum update time
     */
    virtual const uint16_t GetUpdateMinTime() const = 0;

    /**
     * Set the minimum update time
     * @param[in] updateMinTime the minimum update time
     * @return ER_OK on success
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime) = 0;

};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLEE_H_ */