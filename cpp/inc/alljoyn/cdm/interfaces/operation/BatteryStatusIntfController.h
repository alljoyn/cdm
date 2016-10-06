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

#ifndef BATTERYSTATUSINTFCONTROLLER_H_
#define BATTERYSTATUSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusInterface.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface Controller class
 */
class BatteryStatusIntfController : public BatteryStatusInterface {
  public:
    /**
     * Constructor of BatteryStatusIntfController
     */
    BatteryStatusIntfController() {}

    /**
     * Destructor of BatteryStatusIntfController
     */
    virtual ~BatteryStatusIntfController() {}

    /**
     * Get current value of bettery status
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentValue(void* context = NULL) = 0;

    /**
     * Get if battery is being charged
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsCharging(void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTFCONTROLLER_H_ */