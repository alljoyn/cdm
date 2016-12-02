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
#include <alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h>

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
     * Get Volume property
     * (Speaker volume index of the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVolume(void* context = NULL) = 0;

    /**
     * Set Volume property
     * (Speaker volume index of the device.)
     * @param[in] value The volume to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t value, void* context = NULL) = 0;

    /**
     * Get MaxVolume property
     * (Maximum value allowed for Volume.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxVolume(void* context = NULL) = 0;

    /**
     * Get Mute property
     * (If true, state of volume is muted.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMute(void* context = NULL) = 0;

    /**
     * Set Mute property
     * (If true, state of volume is muted.)
     * @param[in] value The mute to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool value, void* context = NULL) = 0;
};

typedef std::shared_ptr<AudioVolumeIntfController> AudioVolumeIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLER_H_ */
