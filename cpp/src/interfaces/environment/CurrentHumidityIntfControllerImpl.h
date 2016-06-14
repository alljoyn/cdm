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

#ifndef CURRENTHUMIDITYINTFCONTROLLERIMPL_H_
#define CURRENTHUMIDITYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/environment/CurrentHumidityIntfController.h>

namespace ajn {
namespace services {

class CurrentHumidityIntfControllerListener;
class HaeProxyBusObject;

/**
 * CurrentHumidity Interface Controller implementation class
 */
class CurrentHumidityIntfControllerImpl : public InterfaceController, public CurrentHumidityIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of CurrentHumidityIntfControllerImpl
     */
    CurrentHumidityIntfControllerImpl(BusAttachment& busAttachment, CurrentHumidityIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of CurrentHumidityIntfControllerImpl
     */
    virtual ~CurrentHumidityIntfControllerImpl();

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
     * Get CurrentHumidity
     * @param[in] context
     * @return status
     */
    QStatus GetCurrentValue(void* context);

    /**
     * Get Max Humidity
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxValue(void* context);

  private:
    CurrentHumidityIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    CurrentHumidityIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLERIMPL_H_ */
