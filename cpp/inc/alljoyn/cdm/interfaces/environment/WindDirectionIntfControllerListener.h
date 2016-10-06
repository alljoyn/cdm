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

#ifndef WINDDIRECTIONINTFCONTROLLERLISTENER_H_
#define WINDDIRECTIONINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * WindDirection interface controller listener class
 */
class WindDirectionIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of WindDirectionIntfControllerListener
     */
    virtual ~WindDirectionIntfControllerListener() {}

    /**
     * Handler for HorizontalDirection property changed
     * @param[in] objectPath the object path
     * @param[in] value horizontal direction
     */
    virtual void OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for HorizontalMax property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum horizontal direction
     */
    virtual void OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for HorizontalAutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] value horizontal auto mode
     */
    virtual void OnHorizontalAutoModeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for VerticalDirection property changed
     * @param[in] objectPath the object path
     * @param[in] value vertical direction
     */
    virtual void OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for VerticalMax property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum vertical direction
     */
    virtual void OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for VerticalAutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] value vertical auto mode
     */
    virtual void OnVerticalAutoModeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for getting HorizontalDirection property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value horizontal direction
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for setting HorizontalDirection property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting HorizontalMax property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum horizontal direction
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for getting HorizontalAutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value horizontal auto mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for setting HorizontalAutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting VerticalDirection property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value vertical direction
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for setting VerticalDirection property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting VerticalMax property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum vertical direction
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for getting VerticalAutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value vertical auto mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for setting VerticalAutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLERLISTENER_H_ */