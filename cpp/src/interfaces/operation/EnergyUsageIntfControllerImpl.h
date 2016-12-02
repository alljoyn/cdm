/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef ENERGYUSAGEINTFCONTROLLERIMPL_H_
#define ENERGYUSAGEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfController.h>

namespace ajn {
namespace services {

class EnergyUsageIntfControllerListener;
class CdmProxyBusObject;

/**
 * EnergyUsage Interface Controller implementation class
 */
class EnergyUsageIntfControllerImpl : public InterfaceController, public EnergyUsageIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of EnergyUsageIntfControllerImpl
     */
    EnergyUsageIntfControllerImpl(BusAttachment& busAttachment, EnergyUsageIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

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