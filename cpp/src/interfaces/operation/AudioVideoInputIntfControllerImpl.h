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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLERIMPL_H_
#define AUDIOVIDEOINPUTINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfController.h>

namespace ajn {
namespace services {

class AudioVideoInputIntfControllerListener;
class CdmProxyBusObject;

/**
 * AudioVideoInput Interface Controller implementation class
 */
class AudioVideoInputIntfControllerImpl : public InterfaceController, public AudioVideoInputIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of AudioVideoInputIntfControllerImpl
     */
    AudioVideoInputIntfControllerImpl(BusAttachment& busAttachment, AudioVideoInputIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of AudioVideoInputIntfControllerImpl
     */
    virtual ~AudioVideoInputIntfControllerImpl();

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
     * Set input source id
     * @param[in] input source id
     * @param[in] context
     * @return status
     */
    virtual QStatus SetInputSourceId(const uint16_t inputSourceId, void* context);

    /**
     * Get input source id
     * @param[in] context
     * @return status
     */
    QStatus GetInputSourceId(void* context);

    /**
     * Get supported input sources
     * @param[in] context
     * @return status
     */
    QStatus GetSupportedInputSources(void* context);

  private:
    AudioVideoInputIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetInputSourceIdPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetInputSourceIdPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedInputSourcesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    AudioVideoInputIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLERIMPL_H_ */
