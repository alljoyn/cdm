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

#ifndef TARGETHUMIDITYMODEL_H_
#define TARGETHUMIDITYMODEL_H_

#include <interfaces/controllee/environment/TargetHumidityIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class TargetHumidityModel : public virtual TargetHumidityIntfControlleeModel {
  public:
    TargetHumidityModel(const std::string& busPath);

    /**
     * Get TargetValue
     * @return current target value
     */
    QStatus GetTargetValue(uint8_t& out) const override;

     /**
     * Set TargetValue
     * @param[in] value The target value to set
     * @return ER_OK on success
     */
    QStatus SetTargetValue(const uint8_t value) override;

    /**
     * Get MinValue
     * @return current min value
     */
    QStatus GetMinValue(uint8_t& out) const override;

    /**
     * Get MaxValue
     * @return current max value
     */
    QStatus GetMaxValue(uint8_t& out) const override;

    /**
     * Get StepValue
     * @return current step value
     */
    QStatus GetStepValue(uint8_t& out) const override;

    /**
     * Get SelectableHumidityLevels
     * @return current selectable humidity levels
     */
    QStatus GetSelectableHumidityLevels(std::vector<uint8_t>& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* TARGETHUMIDITYMODEL_H_ */