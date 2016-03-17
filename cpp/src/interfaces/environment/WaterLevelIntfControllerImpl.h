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

#ifndef WATERLEVELINTFCONTROLLERIMPL_H_
#define WATERLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfController.h>

namespace ajn {
namespace services {

class WaterLevelIntfControllerListener;
class HaeProxyBusObject;

/**
 * WaterLevel Interface Controller implementation class
 */
class WaterLevelIntfControllerImpl : public InterfaceController, public WaterLevelIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of WaterLevelIntfControllerImpl
     */
    WaterLevelIntfControllerImpl(BusAttachment& busAttachment, WaterLevelIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of WaterLevelIntfControllerImpl
     */
    virtual ~WaterLevelIntfControllerImpl();

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
     * Get current water level
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCurrentLevel(void* context = NULL);

    /**
     * Get supply source
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupplySource(void* context = NULL);

    /**
     * Get max level
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxLevel(void* context = NULL);

  private:
    WaterLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void OnGetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void OnGetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void OnGetSupplySourcePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);


    BusAttachment& m_busAttachment;
    WaterLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLERIMPL_H_ */
