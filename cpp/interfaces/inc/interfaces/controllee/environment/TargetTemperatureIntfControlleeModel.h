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

#ifndef TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_
#define TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>
#include <interfaces/common/environment/TargetTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature Model Interface class for the Controllee
 */
class TargetTemperatureIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of TargetTemperatureIntfControlleeModel
     */
    virtual ~TargetTemperatureIntfControlleeModel() {}

    /**
     * Get TargetValue
     * @return current target value
     */
    virtual QStatus GetTargetValue(double& out) const = 0;

     /**
     * Set TargetValue
     * @param[in] value The target value to set
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const double value) = 0;
    /**
     * Get MinValue
     * @return current min value
     */
    virtual QStatus GetMinValue(double& out) const = 0;
    /**
     * Get MaxValue
     * @return current max value
     */
    virtual QStatus GetMaxValue(double& out) const = 0;
    /**
     * Get StepValue
     * @return current step value
     */
    virtual QStatus GetStepValue(double& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_ */
