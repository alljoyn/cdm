/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef FILTERSTATUSINTFCONTROLLEE_H_
#define FILTERSTATUSINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/FilterStatusInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * FilterStatus Interface Controllee class
 */
class FilterStatusIntfControllee final : public CdmControlleeInterface
{
  public:

    /**
     * Constructor of FilterStatusIntfControllee
     */
    FilterStatusIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of FilterStatusIntfControllee
     */
    ~FilterStatusIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the ExpectedLifeInDays property
     * @param[in] newValue new value of expected life in days
     * @return ER_OK on success
     */
    QStatus EmitExpectedLifeInDaysChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the IsCleanable property
     * @param[in] newValue new value of is cleanable
     * @return ER_OK on success
     */
    QStatus EmitIsCleanableChanged(const bool newValue);

    /**
     * Emits a changed signal for the OrderPercentage property
     * @param[in] newValue new value of order percentage
     * @return ER_OK on success
     */
    QStatus EmitOrderPercentageChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the LifeRemaining property
     * @param[in] newValue new value of life remaining
     * @return ER_OK on success
     */
    QStatus EmitLifeRemainingChanged(const uint8_t newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLEE_H_ */