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

#ifndef FANSPEEDLEVELINTFCONTROLLERIMPL_H_
#define FANSPEEDLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/FanSpeedLevelIntfController.h>

namespace ajn {
namespace services {

class FanSpeedLevelIntfControllerListener;
class HaeProxyBusObject;

/**
 * FanSpeedLevel Interface Controller implementation class
 */
class FanSpeedLevelIntfControllerImpl : public InterfaceController, public FanSpeedLevelIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of FanSpeedLevelIntfControllerImpl
     */
    FanSpeedLevelIntfControllerImpl(BusAttachment& busAttachment, FanSpeedLevelIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of FanSpeedLevelIntfControllerImpl
     */
    virtual ~FanSpeedLevelIntfControllerImpl();

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
     * Get current FanSpeedLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetFanSpeedLevel(void* context);

    /**
     * Set FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus SetFanSpeedLevel(const uint8_t value, void* context);

    /**
     * Get MaxFanSpeedLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxFanSpeedLevel(void* context);

    /**
     * Get current AutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetAutoMode(void* context);

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetAutoMode(const uint8_t value, void* context);

  private:
    FanSpeedLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void SetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    FanSpeedLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLERIMPL_H_ */
