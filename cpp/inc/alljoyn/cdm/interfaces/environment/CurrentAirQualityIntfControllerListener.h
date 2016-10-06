/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef CURRENTAIRQUALITYINTFCONTROLLERLISTENER_H_
#define CURRENTAIRQUALITYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controller Listener class
 */
class CurrentAirQualityIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~CurrentAirQualityIntfControllerListener() {}

    /**
     * Callback handler for getting ContaminantType property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value contaminant type
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting CurrentValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value air quality
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting MaxValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of air quality
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting MinValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the minimum value of air quality
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting Precision property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] Precision precision
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context) {}

    /**
     * Callback handler for getting UpdateMinTime property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime the minimum time between updates
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context) {}

    /**
     * Handler for ContaminantType property changed
     * @param[in] objectPath the object path
     * @param[in] value air quality
     */
    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] value air quality
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of air quality
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for MinValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the minimum value of air quality
     */
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] Precision precision
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime the minimum time between updates
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLERLISTENER_H_ */