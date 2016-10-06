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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef WINDDIRECTIONINTFCONTROLLER_H_
#define WINDDIRECTIONINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionInterface.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface Controller class
 */
class WindDirectionIntfController : public WindDirectionInterface {
  public:
    /**
     * Constructor of WindDirectionIntfController
     */
    WindDirectionIntfController() {}

    /**
     * Destructor of WindDirectionIntfController
     */
    virtual ~WindDirectionIntfController() {}

    /**
     * Get horizontal direction
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalDirection (void* context = NULL) = 0;

    /**
     * Set horizontal direction
     * @param[in] value horizontal direction
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalDirection (const uint16_t value, void* context = NULL) = 0;

    /**
     * Get the maximum horizontal direction
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalMax(void* context = NULL) = 0;

    /**
     * Get horizontal auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalAutoMode (void* context = NULL) = 0;

    /**
     * Set horizontal auto mode
     * @param[in] value horizontal auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalAutoMode (const uint8_t value, void* context = NULL) = 0;

    /**
     * Get vertical direction
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalDirection (void* context = NULL) = 0;

    /**
     * Set vertical direction
     * @param[in] value vertical direction
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalDirection (const uint16_t value, void* context = NULL) = 0;

    /**
     * Get the maximum vertical direction
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalMax(void* context = NULL) = 0;

    /**
     * Get vertical auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalAutoMode (void* context = NULL) = 0;

    /**
     * Set vertical auto mode
     * @param[in] value vertical auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalAutoMode (const uint8_t value, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLER_H_ */