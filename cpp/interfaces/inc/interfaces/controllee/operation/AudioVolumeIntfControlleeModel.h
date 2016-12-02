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
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/AudioVolumeInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Model Interface class for the Controllee
 */
class AudioVolumeIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of AudioVolumeIntfControlleeModel
     */
    virtual ~AudioVolumeIntfControlleeModel() {}

    /**
     * Get Volume
     * @return current volume
     */
    virtual QStatus GetVolume(uint8_t& out) const = 0;

     /**
     * Set Volume
     * @param[in] value The volume to set
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t value) = 0;
    /**
     * Get MaxVolume
     * @return current max volume
     */
    virtual QStatus GetMaxVolume(uint8_t& out) const = 0;
    /**
     * Get Mute
     * @return current mute
     */
    virtual QStatus GetMute(bool& out) const = 0;

     /**
     * Set Mute
     * @param[in] value The mute to set
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLEELISTENER_H_ */