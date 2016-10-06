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

#ifndef RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_
#define RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controller Listener class
 */
class RapidModeTimedIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RapidModeTimedIntfControllerListener() {}

    /**
     * Handler for RapidModeMinutesRemaining property changed
     * @param[in] objectPath the object path
     * @param[in] value time remaining in rapid mode
     */
    virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for getting RapidModeMinutesRemaining property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value time remaining in rapid mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for setting RapidModeMinutesRemaining property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting MaxSetMinutes property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum rapid mode set time
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_ */