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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLEE_H_
#define TEMPERATUREDISPLAYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controllee class
 */
class TemperatureDisplayIntfControllee : public TemperatureDisplayInterface {
  public:
    /**
     * Constructor of TemperatureDisplayIntfControllee
     */
    TemperatureDisplayIntfControllee() {}

    /**
     * Destructor of TemperatureDisplayIntfControllee
     */
    virtual ~TemperatureDisplayIntfControllee() {}

    /**
     * Get DisplayTemperatureUnit
     * @return display temperature unit
     */

    virtual const uint8_t GetDisplayTemperatureUnit() = 0;

    /**
     * Set DisplayTemperatureUnit
     * @param[in] temperatureUnit temperature Unit
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t temperatureUnit) = 0;

    /**
     * Get SupportedDisplayTemperatureUnits
     * @return list of supported temerature units
     */
    virtual const std::vector<uint8_t>& GetSupportedDisplayTemperatureUnits() = 0;

    /**
     * Set SupportedDisplayTemperatureUnits
     * @param[in] supportedTemperatureUnits list of supported temperature units
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayTemperatureUnits(const std::vector<uint8_t>& supportedTemperatureUnits) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLEE_H_ */