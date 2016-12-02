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

#ifndef ENERGYUSAGEINTFCONTROLLERLISTENER_H_
#define ENERGYUSAGEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface Controller Listener class
 */
class EnergyUsageIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~EnergyUsageIntfControllerListener() {}

    /**
     * Callback handler for getting CumulativeEnergy property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] cumulativeEnergy cumulative energy
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double cumulativeEnergy, void* context) {}

    /**
     * Callback handler for getting Precision property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] precision precision
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context) {}

    /**
     * Callback handler for getting UpdateMinTime property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] updateMinTime the minimum update time
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context) {}

    /**
     * Callback handler for ResetCumulativeEnergy method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath,
                                                 void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Handler for CumulativeEnergy property changed
     * @param[in] objectPath the object path
     * @param[in] cumulativeEnergy cumulative energy
     */
    virtual void OnCumulativeEnergyChanged(const qcc::String& objectPath, const double cumulativeEnergy) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] precision precision
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] updateMinTime the minimum update time
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime) {}
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLERLISTENER_H_ */