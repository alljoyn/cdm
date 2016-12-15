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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLEE_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/environment/CurrentAirQualityLevelInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * CurrentAirQualityLevel Interface Controllee class
 */
class CurrentAirQualityLevelIntfControllee final : public CdmControlleeInterface
{
  public:
    using ContaminantType = CurrentAirQualityLevelInterface::ContaminantType;

    /**
     * Constructor of CurrentAirQualityLevelIntfControllee
     */
    CurrentAirQualityLevelIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of CurrentAirQualityLevelIntfControllee
     */
    ~CurrentAirQualityLevelIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the ContaminantType property
     * @param[in] newValue new value of contaminant type
     * @return ER_OK on success
     */
    QStatus EmitContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType newValue);

    /**
     * Emits a changed signal for the CurrentLevel property
     * @param[in] newValue new value of current level
     * @return ER_OK on success
     */
    QStatus EmitCurrentLevelChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the MaxLevel property
     * @param[in] newValue new value of max level
     * @return ER_OK on success
     */
    QStatus EmitMaxLevelChanged(const uint8_t newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLEE_H_ */