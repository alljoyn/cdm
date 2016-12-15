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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>
#include <interfaces/common/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel Model Interface class for the Controllee
 */
class MoistureOutputLevelIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:
    using AutoMode = MoistureOutputLevelInterface::AutoMode;

    /**
     * Destructor of MoistureOutputLevelIntfControlleeModel
     */
    virtual ~MoistureOutputLevelIntfControlleeModel() {}

    /**
     * Get MoistureOutputLevel
     * @return current moisture output level
     */
    virtual QStatus GetMoistureOutputLevel(uint8_t& out) const = 0;

     /**
     * Set MoistureOutputLevel
     * @param[in] value The moisture output level to set
     * @return ER_OK on success
     */
    virtual QStatus SetMoistureOutputLevel(const uint8_t value) = 0;
    /**
     * Get MaxMoistureOutputLevel
     * @return current max moisture output level
     */
    virtual QStatus GetMaxMoistureOutputLevel(uint8_t& out) const = 0;
    /**
     * Get AutoMode
     * @return current auto mode
     */
    virtual QStatus GetAutoMode(MoistureOutputLevelInterface::AutoMode& out) const = 0;

     /**
     * Set AutoMode
     * @param[in] value The auto mode to set
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const MoistureOutputLevelInterface::AutoMode value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_ */