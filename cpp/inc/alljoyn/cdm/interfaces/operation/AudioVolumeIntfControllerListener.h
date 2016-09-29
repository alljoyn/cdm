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

#ifndef AUDIOVOLUMEINTFCONTROLLERLISTENER_H_
#define AUDIOVOLUMEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controller Listener class
 */
class AudioVolumeIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of AudioVolumeIntfControllerListener
     */
    virtual ~AudioVolumeIntfControllerListener() {}

    /**
     * Callback handler for GetVolume completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Volume
     *                  (Speaker volume index of the device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for Volume property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Volume
     *                  (Speaker volume index of the device.)
     */
    virtual void OnVolumeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for SetVolume completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetMaxVolume completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxVolume
     *                  (Maximum value allowed for Volume.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxVolume property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of MaxVolume
     *                  (Maximum value allowed for Volume.)
     */
    virtual void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Callback handler for GetMute completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Mute
     *                  (If true, state of volume is muted.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for Mute property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Mute
     *                  (If true, state of volume is muted.)
     */
    virtual void OnMuteChanged(const qcc::String& objectPath, const bool value) {}

    /**
     * Callback handler for SetMute completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLERLISTENER_H_ */
