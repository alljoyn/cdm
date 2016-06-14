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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureLevelIntfController.h>

namespace ajn {
namespace services {

class TargetTemperatureLevelIntfControllerListener;
class HaeProxyBusObject;

/**
 * TargetTemperatureLevel Interface Controller implementation class
 */
class TargetTemperatureLevelIntfControllerImpl : public InterfaceController, public TargetTemperatureLevelIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of TargetTemperatureLevelIntfControllerImpl
     */
    TargetTemperatureLevelIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureLevelIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of TargetTemperatureLevelIntfControllerImpl
     */
    virtual ~TargetTemperatureLevelIntfControllerImpl();

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
     * Get current TargetLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetLevel(void* context);

    /**
     * Set TargetValue
     * @param[in] value TargetLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus SetTargetLevel(const uint8_t value, void* context);

    /**
     * Get MaxLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxLevel(void* context);

    /**
     * Get SelectableTemperatureLevels
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSelectableTemperatureLevels(void* context);

  private:
    TargetTemperatureLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSelectableTemperatureLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TargetTemperatureLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_ */
