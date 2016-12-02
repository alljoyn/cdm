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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLERIMPL_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h>

namespace ajn {
namespace services {

class MoistureOutputLevelIntfControllerListener;

/**
 * MoistureOutputLevel Interface Controller implementation class
 */
class MoistureOutputLevelIntfControllerImpl : public InterfaceController, public MoistureOutputLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of MoistureOutputLevelIntfControllerImpl
     */
    MoistureOutputLevelIntfControllerImpl(BusAttachment& busAttachment, MoistureOutputLevelIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of MoistureOutputLevelIntfControllerImpl
     */
    virtual ~MoistureOutputLevelIntfControllerImpl();

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
     * Get MoistureOutputLevel property
     * (Current level of moisture output.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMoistureOutputLevel(void* context);

    /**
     * Set MoistureOutputLevel property
     * (Current level of moisture output.)
     * @param[in] value The moisture output level to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMoistureOutputLevel(const uint8_t value, void* context);

    /**
     * Get MaxMoistureOutputLevel property
     * (Maximum level of moisture output.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxMoistureOutputLevel(void* context);

    /**
     * Get AutoMode property
     * (Represent enabled/disabled state of the auto mode. The device decides the moisture output level for providing comfortable surroundings automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAutoMode(void* context);

    /**
     * Set AutoMode property
     * (Represent enabled/disabled state of the auto mode. The device decides the moisture output level for providing comfortable surroundings automatically.)
     * @param[in] value The auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const AutoMode value, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    MoistureOutputLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLERIMPL_H_ */
