/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#ifndef HEATINGZONEINTFCONTROLLERLISTENER_H_
#define HEATINGZONEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/operation/HeatingZoneInterface.h>

namespace ajn {
namespace services {

/**
 * HeatingZone Interface Controller Listener class
 */
class HeatingZoneIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of HeatingZoneIntfControllerListener
     */
    virtual ~HeatingZoneIntfControllerListener() {}

    /**
     * Callback handler for GetNumberOfHeatingZones completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of NumberOfHeatingZones
     *                  (Number of heating zones.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetNumberOfHeatingZones(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for NumberOfHeatingZones property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of NumberOfHeatingZones
     *                  (Number of heating zones.)
     */
    virtual void OnNumberOfHeatingZonesChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetMaxHeatingLevels completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxHeatingLevels
     *                  (Max heating levels for each zone.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for MaxHeatingLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxHeatingLevels
     *                  (Max heating levels for each zone.)
     */
    virtual void OnMaxHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}

    /**
     * Callback handler for GetHeatingLevels completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of HeatingLevels
     *                  (Current heating levels for each zone.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) {}

    /**
     * Handler for HeatingLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of HeatingLevels
     *                  (Current heating levels for each zone.)
     */
    virtual void OnHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLERLISTENER_H_ */