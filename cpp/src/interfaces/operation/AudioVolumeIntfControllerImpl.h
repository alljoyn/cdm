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

#ifndef AUDIOVOLUMEINTFCONTROLLERIMPL_H_
#define AUDIOVOLUMEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfController.h>

namespace ajn {
namespace services {

class AudioVolumeIntfControllerListener;
class CdmProxyBusObject;

/**
 * AudioVolume Interface Controller implementation class
 */
class AudioVolumeIntfControllerImpl : public InterfaceController, public AudioVolumeIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of AudioVolumeIntfControlleeImpl
     */
    AudioVolumeIntfControllerImpl(BusAttachment& busAttachment, AudioVolumeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of AudioVolumeIntfControlleeImpl
     */
    virtual ~AudioVolumeIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Set volume
     * @param[in] volume
     * @param[in] context
     * @return status
     */
    virtual QStatus SetVolume(const uint8_t volume, void* context);

    /**
     * Set mute
     * @param[in] mute
     * @param[in] context
     * @return status
     */
    virtual QStatus SetMute(const bool mute, void* context);

    /**
      * Get volume
      * @param[in] context
      * @return status
     */
    virtual QStatus GetVolume(void* context);

    /**
      * Get max volume
      * @param[in] context
      * @return status
     */
    virtual QStatus GetMaxVolume(void* context);

    /**
     * Get mute
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMute(void* context);

  private:
    AudioVolumeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetVolumePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void SetMutePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMutePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    AudioVolumeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLERIMPL_H_ */
