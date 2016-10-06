/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef AUDIOVOLUMEINTFCONTROLLEE_H_
#define AUDIOVOLUMEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controllee class
 */
class AudioVolumeIntfControllee : public AudioVolumeInterface {
  public:
    /**
     * Constructor of AudioVolumeIntfControllee
     */
    AudioVolumeIntfControllee() {}

    /**
     * Destructor of AudioVolumeIntfControllee
     */
    virtual ~AudioVolumeIntfControllee() {}

    /**
     * Get volume
     * @return Volume
     */
    virtual const uint8_t GetVolume() const = 0;

    /**
     * Set volume
     * @param[in] volume volume
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t volume) = 0;

    /**
     * Get the maximum volume
     * @return The maximum volume
     */
    virtual const uint8_t GetMaxVolume() const = 0;

    /**
     * Set the maximum volume
     * @param[in] maxVolume the maximum volume
     * @return ER_OK on success
     */
    virtual QStatus SetMaxVolume(const uint8_t maxVolume) = 0;

    /**
     * Get mute
     * @return Mute
     */
    virtual const bool GetMute() const = 0;

    /**
     * Set mute
     * @param[in] mute mute
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool mute) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLEE_H_ */