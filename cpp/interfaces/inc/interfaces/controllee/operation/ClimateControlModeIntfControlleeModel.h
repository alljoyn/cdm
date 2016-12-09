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

#ifndef CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_
#define CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>
#include <interfaces/common/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Model Interface class for the Controllee
 */
class ClimateControlModeIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:
    using Mode = ClimateControlModeInterface::Mode;
    using OperationalState = ClimateControlModeInterface::OperationalState;

    /**
     * Destructor of ClimateControlModeIntfControlleeModel
     */
    virtual ~ClimateControlModeIntfControlleeModel() {}

    /**
     * Get Mode
     * @return current mode
     */
    virtual QStatus GetMode(ClimateControlModeInterface::Mode& out) const = 0;

     /**
     * Set Mode
     * @param[in] value The mode to set
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const ClimateControlModeInterface::Mode value) = 0;
    /**
     * Get SupportedModes
     * @return current supported modes
     */
    virtual QStatus GetSupportedModes(std::vector<ClimateControlModeInterface::Mode>& out) const = 0;
    /**
     * Get OperationalState
     * @return current operational state
     */
    virtual QStatus GetOperationalState(ClimateControlModeInterface::OperationalState& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_ */