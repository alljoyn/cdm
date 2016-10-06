/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLER_H_
#define TEMPERATUREDISPLAYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controller class
 */
class TemperatureDisplayIntfController : public TemperatureDisplayInterface {
  public:
    /**
     * Constructor of TemperatureDisplayIntfController
     */
    TemperatureDisplayIntfController() {}

    /**
     * Destructor of TemperatureDisplayIntfController
     */
    virtual ~TemperatureDisplayIntfController() {}

    /**
     * Get DisplayTemperatureUnit
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTemperatureUnit(void* context = NULL) = 0;

    /**
     * Set DisplayTemperatureUnit
     * @param[in] temperatureUnit temperature unit
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t temperatureUnit, void* context = NULL) = 0;

    /**
     * Get SupportedDisplayTemperatureUnits
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTemperatureUnits(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLER_H_ */