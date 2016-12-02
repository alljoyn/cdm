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
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfController.h>

namespace ajn {
namespace services {

class FanSpeedLevelIntfControllerListener;
class CdmProxyBusObject;

/**
 * FanSpeedLevel Interface Controller implementation class
 */
class FanSpeedLevelIntfControllerImpl : public InterfaceController, public FanSpeedLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Constructor of FanSpeedLevelIntfControllerImpl
     */
    FanSpeedLevelIntfControllerImpl(BusAttachment& busAttachment, FanSpeedLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

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
     * Get FanSpeedLevel property
     * (Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetFanSpeedLevel(void* context);

    /**
     * Set FanSpeedLevel property
     * (Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).)
     * @param[in] value The fan speed level to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetFanSpeedLevel(const uint8_t value, void* context);

    /**
     * Get MaxFanSpeedLevel property
     * (Maximum level allowed for target fan speed level.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxFanSpeedLevel(void* context);

    /**
     * Get AutoMode property
     * (Enabled/disabled state of the auto mode.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAutoMode(void* context);

    /**
     * Set AutoMode property
     * (Enabled/disabled state of the auto mode.)
     * @param[in] value The auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const AutoMode value, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxFanSpeedLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    FanSpeedLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLERIMPL_H_ */
