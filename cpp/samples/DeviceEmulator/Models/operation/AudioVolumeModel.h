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

#ifndef AUDIOVOLUMEMODEL_H_
#define AUDIOVOLUMEMODEL_H_

#include <interfaces/controllee/operation/AudioVolumeIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class AudioVolumeModel : public virtual AudioVolumeIntfControlleeModel {
  public:
    AudioVolumeModel(const std::string& busPath);

    /**
     * Get Volume
     * @return current volume
     */
    QStatus GetVolume(uint8_t& out) const override;

     /**
     * Set Volume
     * @param[in] value The volume to set
     * @return ER_OK on success
     */
    QStatus SetVolume(const uint8_t value) override;

    /**
     * Get MaxVolume
     * @return current max volume
     */
    QStatus GetMaxVolume(uint8_t& out) const override;

    /**
     * Get Mute
     * @return current mute
     */
    QStatus GetMute(bool& out) const override;

     /**
     * Set Mute
     * @param[in] value The mute to set
     * @return ER_OK on success
     */
    QStatus SetMute(const bool value) override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* AUDIOVOLUMEMODEL_H_ */