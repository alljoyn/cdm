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

// This file is automatically generated. Do not edit it.

#ifndef TEMPERATUREDISPLAYINTFCONTROLLERLISTENER_H_
#define TEMPERATUREDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/userinterfacesettings/TemperatureDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controller Listener class
 */
class TemperatureDisplayIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TemperatureDisplayIntfControllerListener
     */
    virtual ~TemperatureDisplayIntfControllerListener() {}

    /**
     * Callback handler for GetDisplayTemperatureUnit completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of DisplayTemperatureUnit
     *                  (The unit being used to display temperature (0=C, 1=F, 2 =K))
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for DisplayTemperatureUnit property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of DisplayTemperatureUnit
     *                  (The unit being used to display temperature (0=C, 1=F, 2 =K))
     */
    virtual void OnDisplayTemperatureUnitChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetDisplayTemperatureUnit completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetSupportedDisplayTemperatureUnits completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedDisplayTemperatureUnits
     *                  (List of supported temperature units)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for SupportedDisplayTemperatureUnits property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedDisplayTemperatureUnits
     *                  (List of supported temperature units)
     */
    virtual void OnSupportedDisplayTemperatureUnitsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLERLISTENER_H_ */