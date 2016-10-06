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

#ifndef FILTERSTATUSINTFCONTROLLERLISTENER_H_
#define FILTERSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controller Listener class
 */
class FilterStatusIntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of FilterStatusIntfControllerListener
     */
    virtual ~FilterStatusIntfControllerListener() {}

    /**
     * Handler for ExpectedLifeInDays property changed
     * @param[in] objectPath the object path
     * @param[in] value expected life in days
     */
    virtual void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for IsCleanable property changed
     * @param[in] objectPath the object path
     * @param[in] isCleanable is cleanable
     */
    virtual void OnIsCleanableChanged(const qcc::String& objectPath, const bool isCleanable) {}

    /**
     * Handler for OrderPercentage property changed
     * @param[in] objectPath the object path
     * @param[in] value order percentage
     */
    virtual void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for LifeRemaining property changed
     * @param[in] objectPath the object path
     * @param[in] value life remaining
     */
    virtual void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for getting ExpectedLifeInDays property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value expected life in days
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for getting IsCleanable property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isCleanable is cleanable
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool isCleanable, void* context) {}

    /**
     * Callback handler for getting OrderPercentage property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value order percentage
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting Manufacturer property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] manufacturer manufacturer
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& manufacturer, void* context) {}

    /**
     * Callback handler for getting PartNumber property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] partNumber part number
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& partNumber, void* context) {}

    /**
     * Callback handler for getting Url property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] url url
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& url, void* context) {}

    /**
     * Callback handler for getting LifeRemaining property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value life remaining
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLERLISTENER_H_ */