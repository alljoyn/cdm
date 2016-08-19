/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef AUDIOVOLUMEINTFCONTROLLER_H_
#define AUDIOVOLUMEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/operation/AudioVolumeInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controller class
 */
class AudioVolumeIntfController : public AudioVolumeInterface {
  public:
    /**
     * Constructor of AudioVolumeIntfController
     */
    AudioVolumeIntfController() {}

    /**
     * Destructor of AudioVolumeIntfController
     */
    virtual ~AudioVolumeIntfController() {}

    /**
     * Set volume
     * @param[in] volume volume
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t volume, void* context = NULL) = 0;

    /**
     * Set mute
     * @param[in] mute mute
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool mute, void* context = NULL) = 0;

    /**
     * Get volume
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVolume(void* context = NULL) = 0;

    /**
     * Get the maximum volume
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxVolume(void* context = NULL) = 0;

    /**
     * Get mute
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMute(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLER_H_ */
