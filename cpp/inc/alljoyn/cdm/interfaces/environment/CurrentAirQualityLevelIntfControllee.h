/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLEE_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controllee class
 */
class CurrentAirQualityLevelIntfControllee : public CurrentAirQualityLevelInterface {
  public:
    /**
     * Constructor of CurrentAirQualityLevelIntfControllee
     */
    CurrentAirQualityLevelIntfControllee() {}

    /**
     * Destructor of CurrentAirQualityLevelIntfControllee
     */
    virtual ~CurrentAirQualityLevelIntfControllee() {}

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
     * Get current air quality level
     * @return Current air quaility level
     */
    virtual const uint8_t GetCurrentLevel() const = 0;

    /**
     * Set current air qaulity level
     * @param[in] value current air quality level
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentLevel(const uint8_t value) = 0;

    /**
     * Get the maximum level of air quality
     * @return The maximum level of air quality
     */
    virtual const uint8_t GetMaxLevel() const = 0;

    /**
     * Set the maximum level of air quality
     * @param[in] value the maximum level of air quality
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(const uint8_t value) = 0;

 };

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLEE_H_ */