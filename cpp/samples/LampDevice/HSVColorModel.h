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

#ifndef ALLJOYN_HSVCOLOR_H
#define ALLJOYN_HSVCOLOR_H

#include <interfaces/controllee/operation/BrightnessIntfControlleeModel.h>
#include <interfaces/controllee/operation/ColorIntfControlleeModel.h>

class HSVColorModel final :
    public ajn::services::BrightnessIntfControlleeModel,
    public ajn::services::ColorIntfControlleeModel
{
 public:
    HSVColorModel(const std::string& busPath);

    /**
     * Get Brightness
     * @return current brightness
     */
    QStatus GetBrightness(double& out) const override;

    /**
    * Set Brightness
    * @param[in] value The brightness to set
    * @return ER_OK on success
    */
    QStatus SetBrightness(const double value) override;

    /**
     * Get Hue
     * @return current hue
     */
    QStatus GetHue(double& out) const override;

    /**
    * Set Hue
    * @param[in] value The hue to set
    * @return ER_OK on success
    */
    QStatus SetHue(const double value) override;

    /**
     * Get Saturation
     * @return current saturation
     */
    QStatus GetSaturation(double& out) const override;

    /**
    * Set Saturation
    * @param[in] value The saturation to set
    * @return ER_OK on success
    */
    QStatus SetSaturation(const double value) override;

 private:
    std::string m_busPath;
};


#endif //ALLJOYN_HSVCOLOR_H