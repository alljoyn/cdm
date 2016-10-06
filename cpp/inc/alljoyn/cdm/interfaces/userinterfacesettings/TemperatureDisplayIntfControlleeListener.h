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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLEELISTENER_H_
#define TEMPERATUREDISPLAYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controllee Listener class
 */
class TemperatureDisplayIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of TemperatureDisplayIntfControlleeListener
     */
    virtual ~TemperatureDisplayIntfControlleeListener() {}

    /**
     * Handler for setting DisplayTemperatureUnit property
     * @param[in] temperatureUnit temperature unit
     * @return ER_OK on success
     */
    virtual QStatus OnSetDisplayTemperatureUnit(const uint8_t temperatureUnit) = 0;

    /**
     * Handler for getting DisplayTemperatureUnit property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] temperatureUnit temperature unit
     * @return ER_OK on success
     */
    virtual QStatus OnGetDisplayTemperatureUnit(uint8_t& temperatureUnit) = 0;

    /**
     * Handler for getting SupportedDisplayTemperatureUnits
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedDisplayTemperatureUnits the list of supported temperature units
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedDisplayTemperatureUnits(std::vector<uint8_t>& supportedDisplayTemperatureUnits) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLEELISTENER_H_ */