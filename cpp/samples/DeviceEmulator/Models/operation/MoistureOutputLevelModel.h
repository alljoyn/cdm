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

#ifndef MOISTUREOUTPUTLEVELMODEL_H_
#define MOISTUREOUTPUTLEVELMODEL_H_

#include <interfaces/controllee/operation/MoistureOutputLevelIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class MoistureOutputLevelModel : public virtual MoistureOutputLevelIntfControlleeModel {
  public:
    MoistureOutputLevelModel(const std::string& busPath);

    /**
     * Get MoistureOutputLevel
     * @return current moisture output level
     */
    QStatus GetMoistureOutputLevel(uint8_t& out) const override;

     /**
     * Set MoistureOutputLevel
     * @param[in] value The moisture output level to set
     * @return ER_OK on success
     */
    QStatus SetMoistureOutputLevel(const uint8_t value) override;

    /**
     * Get MaxMoistureOutputLevel
     * @return current max moisture output level
     */
    QStatus GetMaxMoistureOutputLevel(uint8_t& out) const override;

    /**
     * Get AutoMode
     * @return current auto mode
     */
    QStatus GetAutoMode(MoistureOutputLevelInterface::AutoMode& out) const override;

     /**
     * Set AutoMode
     * @param[in] value The auto mode to set
     * @return ER_OK on success
     */
    QStatus SetAutoMode(const MoistureOutputLevelInterface::AutoMode value) override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* MOISTUREOUTPUTLEVELMODEL_H_ */