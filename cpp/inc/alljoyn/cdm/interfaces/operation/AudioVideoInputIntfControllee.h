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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLEE_H_
#define AUDIOVIDEOINPUTINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolumeInput Interface Controllee class
 */
class AudioVideoInputIntfControllee : public AudioVideoInputInterface {
  public:
    /**
     * Constructor of AudioVideoInputIntfControllee
     */
    AudioVideoInputIntfControllee() {}

    /**
     * Destructor of AudioVideoInputIntfControllee
     */
    virtual ~AudioVideoInputIntfControllee() {}

    /**
     * Get input source id
     * @return Input source id
     */
    virtual const uint16_t GetInputSourceId() const = 0;

    /**
     * Set input source id
     * @param[in] inputSourceId input source id
     * @return ER_OK on success
     */
    virtual QStatus SetInputSourceId(uint16_t inputSourceId) = 0;

    /**
     * Get supported input sources
     * @return Supported input sources
     */
    virtual const InputSources& GetSupportedInputSources() const = 0;

    /**
     * Set supported input sources
     * @param[in] supportedInputSources supported input sources
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedInputSources(const InputSources& supportedInputSources) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLEE_H_ */