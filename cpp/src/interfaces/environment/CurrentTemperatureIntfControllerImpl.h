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

#ifndef CURRENTTEMPERATUREINTFCONTROLLERIMPL_H_
#define CURRENTTEMPERATUREINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/environment/CurrentTemperatureIntfController.h>

namespace ajn {
namespace services {

class CurrentTemperatureIntfControllerListener;
class HaeProxyBusObject;

/**
 * CurrentTemperature Interface Controller implementation class
 */
class CurrentTemperatureIntfControllerImpl : public InterfaceController, public CurrentTemperatureIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of CurrentTemperatureIntfControllerImpl
     */
    CurrentTemperatureIntfControllerImpl(BusAttachment& busAttachment, CurrentTemperatureIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of CurrentTemperatureIntfControllerImpl
     */
    virtual ~CurrentTemperatureIntfControllerImpl();

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
     * Get CurrentTemperature
     * @param[in] context
     * @return status
     */
    QStatus GetCurrentValue(void* context);

  private:
    CurrentTemperatureIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    CurrentTemperatureIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTTEMPERATUREINTFCONTROLLERIMPL_H_ */
