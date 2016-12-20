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

#ifndef ENERGYUSAGEINTFCONTROLLERLISTENER_H_
#define ENERGYUSAGEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/operation/EnergyUsageInterface.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface Controller Listener class
 */
class EnergyUsageIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of EnergyUsageIntfControllerListener
     */
    virtual ~EnergyUsageIntfControllerListener() {}

    /**
     * Callback handler for GetCumulativeEnergy completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CumulativeEnergy
     *                  (The cumulative energy consumption of the device)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for CumulativeEnergy property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CumulativeEnergy
     *                  (The cumulative energy consumption of the device)
     */
    virtual void OnCumulativeEnergyChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetPrecision completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Precision
     *                  (The precision of the CumulativeEnergy property; i.e., the value the actual energy consumption must change before CumulativeEnergy is updated)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Precision
     *                  (The precision of the CumulativeEnergy property; i.e., the value the actual energy consumption must change before CumulativeEnergy is updated)
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for GetUpdateMinTime completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of UpdateMinTime
     *                  (The minimum time between updates of the CumulativeEnergy property)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of UpdateMinTime
     *                  (The minimum time between updates of the CumulativeEnergy property)
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for ResetCumulativeEnergy completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLERLISTENER_H_ */