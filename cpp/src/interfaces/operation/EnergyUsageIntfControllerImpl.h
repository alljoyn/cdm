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

#ifndef ENERGYUSAGEINTFCONTROLLERIMPL_H_
#define ENERGYUSAGEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/EnergyUsageIntfController.h>

namespace ajn {
namespace services {

class EnergyUsageIntfControllerListener;
class HaeProxyBusObject;

/**
 * EnergyUsage Interface Controller implementation class
 */
class EnergyUsageIntfControllerImpl : public InterfaceController, public EnergyUsageIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of EnergyUsageIntfControllerImpl
     */
    EnergyUsageIntfControllerImpl(BusAttachment& busAttachment, EnergyUsageIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of EnergyUsageIntfControllerImpl
     */
    virtual ~EnergyUsageIntfControllerImpl();

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
     * Get cumulative energy
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCumulativeEnergy(void* context);

    /**
     * Get precision
     * @param[in] context
     * @return status
     */
    virtual QStatus GetPrecision(void* context);

    /**
     * Get the minimum update time
     * @param[in] context
     * @return status
     */
    virtual QStatus GetUpdateMinTime(void* context);

    /**
     * Reset cumulative energy
     * @param[in] context
     * @return status
     */
    virtual QStatus ResetCumulativeEnergy(void* context);

  private:
    EnergyUsageIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void CumulativeEnergyPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void PrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void UpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void ResetCumulativeEnergyReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    EnergyUsageIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLERIMPL_H_ */
