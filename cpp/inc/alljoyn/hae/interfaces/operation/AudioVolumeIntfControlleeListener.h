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

#ifndef AUDIOVOLUMEINTFCONTROLLEELISTENER_H_
#define AUDIOVOLUMEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controllee Listener class
 */
class AudioVolumeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of AudioVolumeIntfControlleeListener
     */
    virtual ~AudioVolumeIntfControlleeListener() {}

    /**
     * Handler for setting Volume property
     * @param[in] volume volume
     * @return ER_OK on success
     */
    virtual QStatus OnSetVolume(const uint8_t& volume) = 0;

    /**
     * Handler for getting Volume property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] volume volume
     * @return ER_OK on success
     */
    virtual QStatus OnGetVolume(uint8_t& volume) = 0;

    /**
     * Handler for getting MaxVolume property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] maxVolume the maximum volume
     * @return ER_OK on success
     */
     virtual QStatus OnGetMaxVolume(uint8_t& maxVolume) = 0;

     /**
      * Handler for setting Mute property
      * @param[in] mute mute
      * @return ER_OK on success
      */
     virtual QStatus OnSetMute(const bool& mute) = 0;

     /**
      * Handler for getting Mute property
      * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
      * @param[out] mute mute
      * @return ER_OK on success
      */
     virtual QStatus OnGetMute(bool& mute) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLEELISTENER_H_ */
