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

#ifndef TARGETTEMPERATUREINTFCONTROLLERIMPL_H_
#define TARGETTEMPERATUREINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureIntfController.h>

namespace ajn {
namespace services {

class TargetTemperatureIntfControllerListener;
class HaeProxyBusObject;

/**
 * TargetTemperature Interface Controller implementation class
 */
class TargetTemperatureIntfControllerImpl : public InterfaceController, public TargetTemperatureIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of TargetTemperatureIntfControllerImpl
     */
    TargetTemperatureIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of TargetTemperatureIntfControllerImpl
     */
    virtual ~TargetTemperatureIntfControllerImpl();

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
     * Get current TargetValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTargetValue(void* context);

    /**
     * Set TargetValue
     * @param[in] TargetValue
     * @param[in] context
     * @return status
     */
    virtual QStatus SetTargetValue(const double value, void* context);

    /**
     * Get MinValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMinValue(void* context);

    /**
     * Get MaxValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxValue(void* context);

    /**
     * Get StepValue
     * @param[in] context
     * @return status
     */
    virtual QStatus GetStepValue(void* context);

  private:
    TargetTemperatureIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetTargetValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMinValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetStepValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TargetTemperatureIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLERIMPL_H_ */
