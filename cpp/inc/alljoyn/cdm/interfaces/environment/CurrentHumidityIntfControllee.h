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

#ifndef CURRENTHUMIDITYINTFCONTROLLEE_H_
#define CURRENTHUMIDITYINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity Interface Controllee class
 */
class CurrentHumidityIntfControllee : public CurrentHumidityInterface {
  public:
    /**
     * Constructor of CurrentHumidityIntfControllee
     */
    CurrentHumidityIntfControllee() {}

    /**
     * Destructor of CurrentHumidityIntfControllee
     */
    virtual ~CurrentHumidityIntfControllee() {}

    /**
     * Get current humidity
     * @return Current humidity
     */
    virtual const uint8_t GetCurrentValue() const = 0;

    /**
     * Set current humidity
     * @param[in] value current humidity
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentValue(const uint8_t value) = 0;

    /**
     * Get MaxValue
     * @return MaxValue
     */
    virtual const uint8_t GetMaxValue() const = 0;

    /**
     * Set MaxValue
     * @param[in] value max humidity
     * @return ER_OK on success
     */
    virtual QStatus SetMaxValue(const uint8_t value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLEE_H_ */