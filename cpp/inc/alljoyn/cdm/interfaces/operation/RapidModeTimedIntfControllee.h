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

#ifndef RAPIDMODETIMEDINTFCONTROLLEE_H_
#define RAPIDMODETIMEDINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedInterface.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controllee class
 */
class RapidModeTimedIntfControllee : public RapidModeTimedInterface {
  public:
    /**
     * Constructor of RapidModeTimedIntfControllee
     */
    RapidModeTimedIntfControllee() {}

    /**
     * Destructor of RapidModeTimedIntfControllee
     */
    virtual ~RapidModeTimedIntfControllee() {}

    /**
     * Get time remaining in rapid mode
     * @return Time remaining in rapid mode
     */
    virtual const uint16_t GetRapidModeMinutesRemaining() const = 0;

    /**
     * Set time remaining in rapid mode
     * @param[in] value time remaining in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus SetRapidModeMinutesRemaining(const uint16_t value) = 0;

    /**
     * Get the maximum rapid mode set time
     * @return The maximum rapid mode set time
     */
    virtual const uint16_t GetMaxSetMinutes() const = 0;

    /**
     * Set the maximum rapid mode set time
     * @param[in] value the maximum rapid mode set time
     * @return ER_OK on success
     */
    virtual QStatus SetMaxSetMinutes(const uint16_t value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLEE_H_ */