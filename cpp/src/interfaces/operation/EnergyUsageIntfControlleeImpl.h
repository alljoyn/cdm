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

#ifndef ENERGYUSAGEINTFCONTROLLEEIMPL_H_
#define ENERGYUSAGEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllee.h>

namespace ajn {
namespace services {

class EnergyUsageIntfControlleeListener;
class CdmBusObject;

/**
 * EnergyUsage Interface Controllee implementation class
 */
class EnergyUsageIntfControlleeImpl : public InterfaceControllee, public EnergyUsageIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of EnergyUsageIntfControlleeImpl
     */
    EnergyUsageIntfControlleeImpl(BusAttachment& busAttachment, EnergyUsageIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of EnergyUsageIntfControlleeImpl
     */
    virtual ~EnergyUsageIntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
     virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Set cumulative energy
     * @return status
     */
    virtual QStatus SetCumulativeEnergy(const double cumulativeEnergy);

    /**
     * Get cumulative energy
     * @return cumulative energy
     */
    virtual const double GetCumulativeEnergy() const { return m_cumulativeEnergy; }

    /**
     * Set precision
     * @return status
     */
    virtual QStatus SetPrecision(const double precision);

    /**
     * Get precision
     * @return precision
     */
    virtual const double GetPrecision() const { return m_precision; }

    /**
     * Set the minimum update time
     * @return status
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime);

    /**
     * Get the minimum update time
     * @return the minimum update time
     */
    virtual const uint16_t GetUpdateMinTime() const { return m_updateMinTime; }

    /**
     * Handler of ResetCumulativeEnergy method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnResetCumulativeEnergy(const InterfaceDescription::Member* member, Message& msg);

  private:
    EnergyUsageIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    EnergyUsageIntfControlleeListener& m_interfaceListener;
    double m_cumulativeEnergy;           // read-only, EmitsChangedSignal
    double m_precision;                  // read-only, EmitsChangedSignal
    uint16_t m_updateMinTime;            // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLEEIMPL_H_ */