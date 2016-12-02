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

#ifndef COLORTEMPERATUREINTFCONTROLLERIMPL_H_
#define COLORTEMPERATUREINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/ColorTemperatureIntfController.h>

namespace ajn {
namespace services {

class ColorTemperatureIntfControllerListener;

/**
 * ColorTemperature Interface Controller implementation class
 */
class ColorTemperatureIntfControllerImpl : public InterfaceController, public ColorTemperatureIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of ColorTemperatureIntfControllerImpl
     */
    ColorTemperatureIntfControllerImpl(BusAttachment& busAttachment, ColorTemperatureIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of ColorTemperatureIntfControllerImpl
     */
    virtual ~ColorTemperatureIntfControllerImpl();

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
     * Get Temperature property
     * (Color temperature of the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTemperature(void* context);

    /**
     * Set Temperature property
     * (Color temperature of the device.)
     * @param[in] value The temperature to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTemperature(const double value, void* context);

    /**
     * Get MinTemperature property
     * (The minimum color temperature supported by the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMinTemperature(void* context);

    /**
     * Get MaxTemperature property
     * (The maximum color temperature supported by the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxTemperature(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMinTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    ColorTemperatureIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* COLORTEMPERATUREINTFCONTROLLERIMPL_H_ */
