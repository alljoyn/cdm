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

#ifndef BRIGHTNESSINTFCONTROLLERIMPL_H_
#define BRIGHTNESSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/BrightnessIntfController.h>

namespace ajn {
namespace services {

class BrightnessIntfControllerListener;

/**
 * Brightness Interface Controller implementation class
 */
class BrightnessIntfControllerImpl : public InterfaceController, public BrightnessIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of BrightnessIntfControllerImpl
     */
    BrightnessIntfControllerImpl(BusAttachment& busAttachment, BrightnessIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of BrightnessIntfControllerImpl
     */
    virtual ~BrightnessIntfControllerImpl();

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
     * Get Brightness property
     * (Brightness of the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetBrightness(void* context);

    /**
     * Set Brightness property
     * (Brightness of the device.)
     * @param[in] value The brightness to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetBrightness(const double value, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetBrightnessPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetBrightnessPropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    BrightnessIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* BRIGHTNESSINTFCONTROLLERIMPL_H_ */
