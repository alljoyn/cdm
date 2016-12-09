/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLEE_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/environment/TargetTemperatureLevelInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * TargetTemperatureLevel Interface Controllee class
 */
class TargetTemperatureLevelIntfControllee final : public CdmControlleeInterface
{
  public:

    /**
     * Constructor of TargetTemperatureLevelIntfControllee
     */
    TargetTemperatureLevelIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TargetTemperatureLevelIntfControllee
     */
    ~TargetTemperatureLevelIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the MaxLevel property
     * @param[in] newValue new value of max level
     * @return ER_OK on success
     */
    QStatus EmitMaxLevelChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the TargetLevel property
     * @param[in] newValue new value of target level
     * @return ER_OK on success
     */
    QStatus EmitTargetLevelChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the SelectableTemperatureLevels property
     * @param[in] newValue new value of selectable temperature levels
     * @return ER_OK on success
     */
    QStatus EmitSelectableTemperatureLevelsChanged(const std::vector<uint8_t>& newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLEE_H_ */