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

#ifndef HEATINGZONEINTFCONTROLLERIMPL_H_
#define HEATINGZONEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/HeatingZoneIntfController.h>

namespace ajn {
namespace services {

class HeatingZoneIntfControllerListener;
class HaeProxyBusObject;

/**
 * HeatingZone Interface Controller implementation class
 */
class HeatingZoneIntfControllerImpl : public InterfaceController, public HeatingZoneIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of HeatingZoneIntfControllerImpl
     */
    HeatingZoneIntfControllerImpl(BusAttachment& busAttachment, HeatingZoneIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of HeatingZoneIntfControllerImpl
     */
    virtual ~HeatingZoneIntfControllerImpl();

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

    virtual QStatus GetNumberOfHeatingZones(void* context);

    virtual QStatus GetMaxHeatingLevels(void* context );

    virtual QStatus GetHeatingLevels(void* context);

  private:
    HeatingZoneIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetNumberOfHeatingZonesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetMaxHeatingLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetHeatingLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    HeatingZoneIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLERIMPL_H_ */
