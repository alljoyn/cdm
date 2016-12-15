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

#ifndef WATERLEVELINTFCONTROLLERLISTENER_H_
#define WATERLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/environment/WaterLevelInterface.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface Controller Listener class
 */
class WaterLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    using SupplySource = WaterLevelInterface::SupplySource;

    /**
     * Destructor of WaterLevelIntfControllerListener
     */
    virtual ~WaterLevelIntfControllerListener() {}

    /**
     * Callback handler for GetSupplySource completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupplySource
     *                  (The supply source of water.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupplySource(QStatus status, const qcc::String& objectPath, const WaterLevelInterface::SupplySource value, void* context) {}

    /**
     * Handler for SupplySource property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupplySource
     *                  (The supply source of water.)
     */
    virtual void OnSupplySourceChanged(const qcc::String& objectPath, const WaterLevelInterface::SupplySource value) {}

    /**
     * Callback handler for GetCurrentLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentLevel
     *                  (The current level of water in the tank.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for CurrentLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentLevel
     *                  (The current level of water in the tank.)
     */
    virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetMaxLevel completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxLevel
     *                  (Maximum level allowed for water level.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxLevel
     *                  (Maximum level allowed for water level.)
     */
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) {}
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLERLISTENER_H_ */